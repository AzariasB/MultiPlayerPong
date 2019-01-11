#! /usr/local/bin/ruby

require 'date'
require 'builder'
require 'nokogiri'
require 'json'

def LICENCE(filename)
	return  %{/*
 * The MIT License
 *
 * Copyright 2017-#{Date.today.year} azarias.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
/*
 * File:   #{filename}
 * Author: azarias
 *
 * Created on #{Date.today.strftime("%d/%m/%Y")}
 */
/*
 * This file is automatically generated
 * All modifications done to this file may be lost
 */
	}
end

HPP_TEMPLATE =  %{#{LICENCE('Assets.hpp')}

#pragma once

#include <unordered_map>
#include <SFML/Config.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/String.hpp>

namespace mp{

class Assets
{
public:
  #CONTENT

private:
    Assets();

};

}
}

CPP_TEMPLATE = %{#{LICENCE('Assets.cpp')}

#include "Assets.hpp"

namespace mp{
#CONTENT
}

}

class String
  def camel_case
    split('_').map{|e| e.capitalize}.join
  end
end

@atlases = {}
@i18ns = []

def parse_atlases(folder, dic)
  Dir[folder + "/*.xml"].each{|x|
    doc = File.open(x){|x|Nokogiri::XML(x)}
    image = doc.xpath("//TextureAtlas").attr("imagePath")
    atlas_name = File.basename(image.to_s, ".*")
    @atlases[atlas_name] = {:atlases => [], :path => "res/atlases/" + image.to_s}

    doc.xpath("//SubTexture").each{|st|
      @atlases[atlas_name][:atlases] << {:name => File.basename(st["name"].to_s, ".*") + atlas_name.camel_case,
                   :x => st["x"].to_i,
                   :y => st["y"].to_i,
                   :height => st["height"].to_i,
                   :width => st["width"].to_i
      }
    }

  }

end

def parse_i18n(folder, dic)
  Dir[folder + "/*.json"].each{|x|
    @i18ns << JSON.parse(File.read(x))

  }
end

def parseFolder(folder, dic)

  Dir.foreach(folder) do |file|
    next if file == ".." or file == "."

    fullFile = "#{folder}/#{file}"

    if File.file?(fullFile)
      short = File.basename(folder)
      dic[short] = [] if not dic[short]

      dic[short] << file
    elsif File.directory?(fullFile)
      if fullFile =~ /atlases$/
        parse_atlases(fullFile, dic)
      elsif fullFile =~ /i18n$/
        parse_i18n(fullFile, dic)
      else
        parseFolder(fullFile, dic)
      end

    end
  end

  return dic
end

def translation_tocppmap(tr)

end

def build_rcc(files)
  xml = Builder::XmlMarkup.new( :indent => 2 )
  xml.instruct! :xml, :encoding => "UTF-8"
  xml.RCC do |p|
    files.each do |k,v|
      p.qresource("prefix" => "/#{k}") do |res|
        v.each do |f_name|
          res.file("res/#{k}/#{f_name}", "alias" => f_name.downcase())
        end
      end
    end
    return if not @atlases.size
    p.qresource("prefix" => "/atlases") do |res|
      @atlases.each{|k,v|
        p.file("res/atlases/#{k}.png", "alias" => "#{k}.png")
      }
    end
  end
end

def to_intrect(x)
  return "sf::IntRect(#{x[:x]}, #{x[:y]}, #{x[:width]}, #{x[:height]})"
end

def build_cpp(files)
  cpp_content = ""
  hpp_content = ""
  counter = 0
  files.each do |k,v|
    c_case = k.camel_case
    enum_val = v.map{|x| File.basename(x, ".*").camel_case + " = #{counter+=1}"}
    hpp_content += %{
    enum #{c_case} {#{enum_val*", "}};
    static const std::unordered_map<sf::Uint64, std::string> #{k};
}
    init = v.map{|x|
      name = File.basename(x, ".*").camel_case
      "{ Assets::#{c_case}::#{name}, \":/#{k}/#{x.downcase}\" }"
    }

    cpp_content += %{
const std::unordered_map<sf::Uint64, std::string> Assets::#{k} = {\n#{init*",\n"}\n};
}
  end
  atlas_enum = []
  atlas_files = {}

  @atlases.each do |k,v|
    at_name = k.camel_case
    atlas_id = counter += 1
    atlas_enum << at_name + " = #{atlas_id}"
    atlas_files[at_name] = ":/atlases/#{k}.png"

    atlases = v[:atlases].map{|x|
        "static const Holder #{x[:name]};"
    }

    hpp_content += %{
    class #{at_name}Atlas {
      public:
        struct Holder {
          const sf::Uint64 textureId = #{atlas_id};
          const sf::IntRect bounds;
        };

        #{atlases*"\n        "}
    };
}

    atlases = v[:atlases].map{|x|
        "const Assets::#{at_name}Atlas::Holder Assets::#{at_name}Atlas::#{x[:name]} = {#{atlas_id}, #{to_intrect(x)} };"
    }

    cpp_content += "\n" + atlases*"\n" + "\n"

  end

  hpp_content += %{
    class I18N {
    public:
      struct Translation {
        const sf::String name;
        const std::unordered_map<std::string, sf::String> translation;
      };

      static const std::unordered_map<std::string, Translation> translations;
    };
}

  cpp_content += "const std::unordered_map<std::string, Assets::I18N::Translation> Assets::I18N::translations = {\n"
  cpp_content +=  @i18ns.map {|x|
     %{   {"#{x['lang']}", { L"#{x['name']}", {#{x['translations'].map{|k,v| "{\"#{k}\",L\"#{v}\"}"}*", " } }}}}
  }*",\n"
  cpp_content += "\n};"

  hpp_content += %{
    enum Atlases {#{atlas_enum*", "}};
    static const std::unordered_map<sf::Uint64, std::string> atlases;
}


  atlas_content = atlas_files.map{|k,v|
    "{ Assets::Atlases::#{k} , \"#{v}\" }"
  }*",\n"
  cpp_content += %{
const std::unordered_map<sf::Uint64, std::string> Assets::atlases = {
#{atlas_content}
};
}

  [hpp_content, cpp_content]
end

res = parseFolder("#{Dir.pwd}/res", {})
rcc = build_rcc(res)
puts rcc
File.write("resources.qrc", build_rcc(res))
cpp = build_cpp(res)

File.write("src/client/Assets.hpp", HPP_TEMPLATE.gsub("#CONTENT", cpp[0]))
File.write("src/client/Assets.cpp", CPP_TEMPLATE.gsub("#CONTENT", cpp[1]))
