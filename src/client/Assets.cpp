/*
 * The MIT License
 *
 * Copyright 2017-2018 azarias.
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
 * File:   Assets.cpp
 * Author: azarias
 *
 * Created on 01/08/2018
 */
/*
 * This file is automatically generated
 * All modifications done to this file may be lost
 */
	

#include "Assets.hpp"

namespace mp{

const std::unordered_map<sf::Uint64, std::string> Assets::fonts = {
{ Assets::Fonts::Caveatbrushregular, ":/fonts/caveatbrushregular.ttf" },
{ Assets::Fonts::Quicksand, ":/fonts/quicksand.otf" }
};

const std::unordered_map<sf::Uint64, std::string> Assets::sounds = {
{ Assets::Sounds::Bounce, ":/sounds/bounce.wav" },
{ Assets::Sounds::Loose, ":/sounds/loose.wav" },
{ Assets::Sounds::Click1, ":/sounds/click1.wav" },
{ Assets::Sounds::Rollover1, ":/sounds/rollover1.wav" },
{ Assets::Sounds::PingPong8bitBiiip, ":/sounds/ping_pong_8bit_biiip.wav" },
{ Assets::Sounds::Win, ":/sounds/win.wav" },
{ Assets::Sounds::Click3, ":/sounds/click3.wav" },
{ Assets::Sounds::Click4, ":/sounds/click4.wav" },
{ Assets::Sounds::Click2, ":/sounds/click2.wav" },
{ Assets::Sounds::PingPong8bitBeeep, ":/sounds/ping_pong_8bit_beeep.ogg" },
{ Assets::Sounds::Click5, ":/sounds/click5.wav" }
};

const std::unordered_map<sf::Uint64, std::string> Assets::shaders = {
{ Assets::Shaders::Alpha, ":/shaders/alpha.frag" }
};

const std::unordered_map<sf::Uint64, std::string> Assets::animations = {
{ Assets::Animations::BallRetract, ":/animations/ball_retract.png" },
{ Assets::Animations::BallExtend, ":/animations/ball_extend.png" },
{ Assets::Animations::PaddleExtend, ":/animations/paddle_extend.png" },
{ Assets::Animations::PaddleRetract, ":/animations/paddle_retract.png" }
};

const std::unordered_map<sf::Uint64, std::string> Assets::icons = {
{ Assets::Icons::Qt, ":/icons/qt.png" },
{ Assets::Icons::Box2d, ":/icons/box2d.png" },
{ Assets::Icons::Sfml32x32, ":/icons/sfml32x32.png" },
{ Assets::Icons::Sfml, ":/icons/sfml.png" },
{ Assets::Icons::Cursor, ":/icons/cursor.png" }
};

const Assets::IconAtlas::Holder Assets::IconAtlas::arrowDownIcon = {24, sf::IntRect(0, 1200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::arrowLeftIcon = {24, sf::IntRect(0, 1100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::arrowRightIcon = {24, sf::IntRect(0, 1000, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::arrowUpIcon = {24, sf::IntRect(0, 900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::audioOffIcon = {24, sf::IntRect(0, 800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::audioOnIcon = {24, sf::IntRect(0, 700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::barsHorizontalIcon = {24, sf::IntRect(0, 600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::barsVerticalIcon = {24, sf::IntRect(0, 500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::button1Icon = {24, sf::IntRect(0, 400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::button2Icon = {24, sf::IntRect(0, 300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::button3Icon = {24, sf::IntRect(0, 200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonAIcon = {24, sf::IntRect(0, 100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonBIcon = {24, sf::IntRect(0, 0, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonLIcon = {24, sf::IntRect(200, 1200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonL1Icon = {24, sf::IntRect(500, 300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonL2Icon = {24, sf::IntRect(500, 200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonRIcon = {24, sf::IntRect(500, 100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonR1Icon = {24, sf::IntRect(500, 0, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonR2Icon = {24, sf::IntRect(400, 1900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonSelectIcon = {24, sf::IntRect(400, 1800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonStartIcon = {24, sf::IntRect(400, 1700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonXIcon = {24, sf::IntRect(400, 1600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonYIcon = {24, sf::IntRect(400, 1500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::checkmarkIcon = {24, sf::IntRect(400, 1400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::contrastIcon = {24, sf::IntRect(400, 1300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::crossIcon = {24, sf::IntRect(400, 1200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::downIcon = {24, sf::IntRect(400, 1100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::downLeftIcon = {24, sf::IntRect(400, 1000, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::downRightIcon = {24, sf::IntRect(400, 900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::exclamationIcon = {24, sf::IntRect(400, 800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::exitIcon = {24, sf::IntRect(400, 700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::exitLeftIcon = {24, sf::IntRect(400, 600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::exitRightIcon = {24, sf::IntRect(400, 500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::exportIcon = {24, sf::IntRect(400, 400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::fastForwardIcon = {24, sf::IntRect(400, 300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::gamepadIcon = {24, sf::IntRect(400, 200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::gamepad1Icon = {24, sf::IntRect(400, 100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::gamepad2Icon = {24, sf::IntRect(400, 0, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::gamepad3Icon = {24, sf::IntRect(300, 1900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::gamepad4Icon = {24, sf::IntRect(300, 1800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::gearIcon = {24, sf::IntRect(300, 1700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::homeIcon = {24, sf::IntRect(300, 1600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::importIcon = {24, sf::IntRect(300, 1500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::informationIcon = {24, sf::IntRect(300, 1400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::joystickIcon = {24, sf::IntRect(300, 1300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::joystickLeftIcon = {24, sf::IntRect(300, 1200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::joystickRightIcon = {24, sf::IntRect(300, 1100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::joystickUpIcon = {24, sf::IntRect(300, 1000, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::largerIcon = {24, sf::IntRect(300, 900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::leaderboardsComplexIcon = {24, sf::IntRect(300, 800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::leaderboardsSimpleIcon = {24, sf::IntRect(300, 700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::leftIcon = {24, sf::IntRect(300, 600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::lockedIcon = {24, sf::IntRect(300, 500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::massiveMultiplayerIcon = {24, sf::IntRect(300, 400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::medal1Icon = {24, sf::IntRect(300, 300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::medal2Icon = {24, sf::IntRect(300, 200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::menuGridIcon = {24, sf::IntRect(300, 100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::menuListIcon = {24, sf::IntRect(300, 0, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::minusIcon = {24, sf::IntRect(200, 1900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::mouseIcon = {24, sf::IntRect(200, 1800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::movieIcon = {24, sf::IntRect(200, 1700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::multiplayerIcon = {24, sf::IntRect(200, 1600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::musicOffIcon = {24, sf::IntRect(200, 1500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::musicOnIcon = {24, sf::IntRect(200, 1400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::nextIcon = {24, sf::IntRect(200, 1300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::openIcon = {24, sf::IntRect(500, 400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::pauseIcon = {24, sf::IntRect(200, 1100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::phoneIcon = {24, sf::IntRect(200, 1000, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::plusIcon = {24, sf::IntRect(200, 900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::powerIcon = {24, sf::IntRect(200, 800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::previousIcon = {24, sf::IntRect(200, 700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::questionIcon = {24, sf::IntRect(200, 600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::returnIcon = {24, sf::IntRect(200, 500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::rewindIcon = {24, sf::IntRect(200, 400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::rightIcon = {24, sf::IntRect(200, 300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::saveIcon = {24, sf::IntRect(200, 200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::scrollHorizontalIcon = {24, sf::IntRect(200, 100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::scrollVerticalIcon = {24, sf::IntRect(200, 0, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::share1Icon = {24, sf::IntRect(100, 1900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::share2Icon = {24, sf::IntRect(100, 1800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::shoppingBasketIcon = {24, sf::IntRect(100, 1700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::shoppingCartIcon = {24, sf::IntRect(100, 1600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::siganl1Icon = {24, sf::IntRect(100, 1500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::signal2Icon = {24, sf::IntRect(100, 1400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::signal3Icon = {24, sf::IntRect(100, 1300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::singleplayerIcon = {24, sf::IntRect(100, 1200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::smallerIcon = {24, sf::IntRect(100, 1100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::starIcon = {24, sf::IntRect(100, 1000, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::stopIcon = {24, sf::IntRect(100, 900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::tabletIcon = {24, sf::IntRect(100, 800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::targetIcon = {24, sf::IntRect(100, 700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::trashcanIcon = {24, sf::IntRect(100, 600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::trashcanOpenIcon = {24, sf::IntRect(100, 500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::trophyIcon = {24, sf::IntRect(100, 400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::unlockedIcon = {24, sf::IntRect(100, 300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::upIcon = {24, sf::IntRect(100, 200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::upLeftIcon = {24, sf::IntRect(100, 100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::upRightIcon = {24, sf::IntRect(100, 0, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::videoIcon = {24, sf::IntRect(0, 1900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::warningIcon = {24, sf::IntRect(0, 1800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::wrenchIcon = {24, sf::IntRect(0, 1700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::zoomIcon = {24, sf::IntRect(0, 1600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::zoomDefaultIcon = {24, sf::IntRect(0, 1500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::zoomInIcon = {24, sf::IntRect(0, 1400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::zoomOutIcon = {24, sf::IntRect(0, 1300, 100, 100) };
const std::unordered_map<std::string, Assets::I18N::Translation> Assets::I18N::translations = {
   {"fr", { L"Français", {{"solo",L"Solo"}, {"multi",L"Multijoueur"}, {"options",L"Options"}, {"credits",L"Crédits"}, {"quit",L"Quitter"}, {"confirm",L"Confirmer"}, {"cancel",L"Annuler"}, {"invalid_ip",L"IP invalide"}, {"entered_invalid_id",L"L'IP entrée est invalide"}, {"toggle_sound",L"Changer son"}, {"key_bindings",L"Contrôles clavier"}, {"fullscreen",L"Plein écran"}, {"menu",L"Menu"}, {"play",L"Jouer"}, {"go_up",L"Monter"}, {"go_down",L"Descendre"}, {"reset",L"Réinitialiser"}, {"back",L"Retour"}, {"really_quit",L"Voulez-vous vraiment quitter ?"}, {"yes",L"Oui"}, {"no",L"Non"}, {"resume",L"Reprendre"}, {"restart",L"Recommencer"}, {"pause",L"Pause"}, {"ok",L"Ok"}, {"programming",L"Programmation"}, {"drawing",L"Dessins"}, {"sounds",L"Sons"}, {"icons",L"Icônes"}, {"font",L"Police"}, {"connecting",L"Connexion"}, {"error",L"Erreur"}, {"failed_connect",L"Échec de la connexion au serveur"}, {"enter_ip",L"Entrez l'adresse du serveur"}, {"waiting_player",L"En attente d'un joueur..."}, {"finished",L"Terminé !"}, {"you_won",L"Vous avez gagné !"}, {"you_lost",L"Vous avez perdu :("}, {"press_key",L"Appuyez sur une touche"}, {"change_key",L"Changer de touche"}, {"Up",L"Haut"}, {"Down",L"Bas"}, {"language",L"Langue"}, {"won",L"a gagné"} }}},
   {"es", { L"Español", {{"solo",L"Solo"}, {"multi",L"Multijugador"}, {"options",L"Opciones"}, {"credits",L"Créditos"}, {"quit",L"Dejar"}, {"confirm",L"Confirmar"}, {"cancel",L"Cancelar"}, {"invalid_ip",L"IP no es válida"}, {"entered_invalid_id",L"La ip que escribiste no es válida"}, {"toggle_sound",L"Alternar el sonido"}, {"key_bindings",L"Asociaciones de teclas"}, {"fullscreen",L"Pantalla completa"}, {"menu",L"Menú"}, {"play",L"Jugar"}, {"go_up",L"Subir"}, {"go_down",L"Bajar"}, {"reset",L"Reiniciar"}, {"back",L"Espalda"}, {"really_quit",L"¿ Realmente quieres salir ?"}, {"yes",L"Sí"}, {"no",L"No"}, {"resume",L"Continuar"}, {"restart",L"Reiniciar"}, {"pause",L"Pausa"}, {"ok",L"Ok"}, {"programming",L"Programación"}, {"drawing",L"Dibujos"}, {"sounds",L"Sonidos"}, {"icons",L"Iconos"}, {"font",L"Tipo de letra"}, {"connecting",L"Conectando"}, {"error",L"Error"}, {"failed_connect",L"Error al conectar con el servidor"}, {"enter_ip",L"Ingrese la dirección IP del servidor"}, {"waiting_player",L"Esperando un jugador ..."}, {"finished",L"Terminado !"}, {"you_won",L"Ganaste !"}, {"you_lost",L"Perdiste :("}, {"press_key",L"Presione una tecla"}, {"change_key",L"Cambiar tecla"}, {"Up",L"Arriba"}, {"Down",L"Abajo"}, {"language",L"Idioma"}, {"won",L"ganado"} }}},
   {"en", { L"English", {{"solo",L"Solo"}, {"multi",L"Multiplayer"}, {"options",L"Options"}, {"credits",L"Credits"}, {"quit",L"Quit"}, {"confirm",L"Confirm"}, {"cancel",L"Cancel"}, {"invalid_ip",L"Invalid IP"}, {"entered_invalid_id",L"The IP you entered is invalid"}, {"toggle_sound",L"Toggle sound"}, {"key_bindings",L"Key bindings"}, {"fullscreen",L"Fullscreen"}, {"menu",L"Menu"}, {"play",L"Play"}, {"go_up",L"Go up"}, {"go_down",L"Go down"}, {"reset",L"Reset"}, {"back",L"Back"}, {"really_quit",L"Do you really want to quit ?"}, {"yes",L"Yes"}, {"no",L"No"}, {"resume",L"Resume"}, {"restart",L"Restart"}, {"pause",L"Pause"}, {"ok",L"Ok"}, {"programming",L"Programming"}, {"drawing",L"Drawing"}, {"sounds",L"Sounds"}, {"icons",L"Icons"}, {"font",L"Font"}, {"connecting",L"Connecting"}, {"error",L"Error"}, {"failed_connect",L"Failed to connect to the server"}, {"enter_ip",L"Enter server ip"}, {"waiting_player",L"Waiting player..."}, {"finished",L"Finished !"}, {"you_won",L"You won !"}, {"you_lost",L"You lost"}, {"press_key",L"Press a key"}, {"change_key",L"Change key"}, {"Up",L"Up"}, {"Down",L"Down"}, {"language",L"Language"}, {"won",L"won"} }}},
   {"it", { L"Italiano", {{"solo",L"Assolo"}, {"multi",L"Multigiocatore"}, {"options",L"Opzioni"}, {"credits",L"Crediti"}, {"quit",L"Smettere"}, {"confirm",L"Confermare"}, {"cancel",L"Annulla"}, {"invalid_ip",L"IP non valid"}, {"entered_invalid_id",L"L'IP inserito non è valido"}, {"toggle_sound",L"Cambia suono"}, {"key_bindings",L"Rilegatura di tastiera"}, {"fullscreen",L"A schermo intero"}, {"menu",L"Menu"}, {"play",L"Giocare"}, {"go_up",L"Salire"}, {"go_down",L"Scendere"}, {"reset",L"Reset"}, {"back",L"Ritorno"}, {"really_quit",L"Vuole realmente finire ?"}, {"yes",L"Sì"}, {"no",L"No"}, {"resume",L"Riprendere"}, {"restart",L"Ricominciare"}, {"pause",L"Pausa"}, {"ok",L"Ok"}, {"programming",L"Programmazione"}, {"drawing",L"Disegni"}, {"sounds",L"Suoni"}, {"icons",L"Icone"}, {"font",L"Font"}, {"connecting",L"Collegamento"}, {"error",L"Errore"}, {"failed_connect",L"Insuccesso della connessione al server"}, {"enter_ip",L"Inserisci l'indirizzo IP del server"}, {"waiting_player",L"In attesa di un giocatore"}, {"finished",L"Finito !"}, {"you_won",L"Hai vinto !"}, {"you_lost",L"Hai perso :("}, {"press_key",L"Appoggi su un tasto"}, {"change_key",L"Cambiare tasto"}, {"Up",L"Alto"}, {"Down",L"basso"}, {"language",L"Lingua"}, {"won",L"a vinto"} }}}
};
const std::unordered_map<sf::Uint64, std::string> Assets::atlases = {
{ Assets::Atlases::Icon , ":/atlases/icon.png" }
};

}

