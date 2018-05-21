#! /usr/bin/ruby
require 'builder'

def parseFolder(folder, dic)

  Dir.foreach(folder) do |file|
    next if file == ".." or file == "."

    fullFile = "#{folder}/#{file}"

    if File.file?(fullFile)
      short = File.basename(folder)

      dic[short] = [] if not dic[short]

      dic[short] << file
    elsif File.directory?(fullFile)
      parseFolder(fullFile, dic)
    end
  end

  return dic
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
  end
end

res = parseFolder("#{Dir.pwd}/res", {})
puts build_rcc(res)
File.write("resources.qrc", build_rcc(res))