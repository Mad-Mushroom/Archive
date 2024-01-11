-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Erstellungszeit: 24. Nov 2023 um 12:19
-- Server-Version: 10.4.22-MariaDB
-- PHP-Version: 8.1.2

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Datenbank: `quizduell_login`
--

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `login`
--

CREATE TABLE `login` (
  `id` int(11) NOT NULL,
  `name` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `email` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `password` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `totalpoints` int(11) NOT NULL,
  `completedquizzes` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL CHECK (json_valid(`completedquizzes`))
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Daten für Tabelle `login`
--

INSERT INTO `login` (`id`, `name`, `email`, `password`, `totalpoints`, `completedquizzes`) VALUES
(1, 'admin', 'admin', '1G9AZPU=', 2147483639, '{\"allgemeinwissen1\":\"false\",\"Allgemeinwissen1\":true,\"Allgemeinwissen2\":true,\"Datei Formate\":true,\"TestQuiz\":true,\"Allgemeinwissen3\":true,\"Allgemeinwissen5\":true}'),
(2, 'testuser', 'test@test.com', 'wW5eeQ==', -2147481711, '{\"allgemeinwissen1\":\"false\",\"Allgemeinwissen1\":true,\"TestQuiz\":true,\"Allgemeinwissen2\":true,\"Datei Formate\":true}'),
(3, 'Markus Darkus', 'darkus666@markus.com', 'xH5Ed/8S4n1/iA==', 254, '{\"allgemeinwissen1\":\"false\",\"Allgemeinwissen1\":true,\"Datei Formate\":true,\"Allgemeinwissen2\":true,\"TestQuiz\":true}'),
(4, 'Paul Paulson', 'paul@gmail.com', 'xH5Edw==', 0, '{\"allgemeinwissen1\": \"false\"}'),
(5, 'Heinz Meier', 'h.meier@gmx.de', 'wX5PbK4=', 3, '{\"allgemeinwissen1\":\"false\",\"Allgemeinwissen2\":true}'),
(6, 'Mike', 'mike.nobert@gmail.com', 'njkdP6s28nhpmg==', 246, '{\"allgemeinwissen1\":\"false\",\"Allgemeinwissen1\":true,\"Datei Formate\":true}'),
(7, 'xX_Destroyer_Xx', 'destroyer2001@hotmail.de', '0W5eeekI/g==', 74, '{\"allgemeinwissen1\":\"false\",\"Datei Formate\":true,\"Allgemeinwissen2\":true}'),
(8, 'COOLboi', 'coolboi69@msn.com', '3GpAbvQI6w==', 1, '{\"allgemeinwissen1\":\"false\",\"god damn\":true}'),
(9, 'Alexander Siegert', 'siegert.a.2001@hotmail.de', 'zGRYYfcJ4md2ywlGrKKjuuJ3vuBhctHe', 2, '{\"allgemeinwissen1\":\"false\",\"Allgemeinwissen2\":true}'),
(10, 'Günther Holzner', 'holzi@holzverarbeitungholzner.de', '0GVJYfIE72BpzAdQqKa/su5q7A==', 7, '{\"allgemeinwissen1\":\"false\",\"Datei Formate\":true}'),
(11, '--SIRIUS--', 'siriusblack@gmail.com', 'mCZeZOkOqjw=', 5, '{\"allgemeinwissen1\":\"false\",\"Allgemeinwissen1\":true,\"god damn\":true}'),
(12, 'counterspieler', 'spieler#19473@cskeller.de', '3HlKaPUD8HBg', 0, '{\"allgemeinwissen1\": \"false\"}'),
(16, 'dunkus', 'dunkus@gmail.com', '0X5DZvI=', 10, '{\"allgemeinwissen1\":\"false\",\"Allgemeinwissen1\":true}'),
(17, 'chungus', 'chungus@chungusindustries.com', '1mNYY/wS9A==', 0, '{\"allgemeinwissen1\": \"false\"}'),
(18, 'big chungus', 'bigchungus@chungusindustries.com', '12JKbvMS6XZmyg==', 0, '{\"allgemeinwissen1\": \"false\"}'),
(19, 'giftgasmuecke', 'giftgas@mueckenmail.de', '1ngcI60G631y', 0, '{\"allgemeinwissen1\": \"false\"}'),
(20, 'Benjamin', 'test@gmail.com', '3WpBYfQ=', 10, '{\"allgemeinwissen1\":\"false\",\"Allgemeinwissen1\":true,\"irgendwas\":true}');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `multiplayer`
--

CREATE TABLE `multiplayer` (
  `id` int(11) NOT NULL,
  `roomcode` int(11) NOT NULL,
  `quiz` text COLLATE utf8_unicode_ci NOT NULL,
  `name` text COLLATE utf8_unicode_ci NOT NULL,
  `password` text COLLATE utf8_unicode_ci NOT NULL,
  `players` int(11) NOT NULL,
  `player1points` int(11) NOT NULL,
  `player2points` int(11) NOT NULL,
  `playersdone` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Daten für Tabelle `multiplayer`
--

INSERT INTO `multiplayer` (`id`, `roomcode`, `quiz`, `name`, `password`, `players`, `player1points`, `player2points`, `playersdone`) VALUES
(35, 23232, 'Allgemeinwissen1', 'chungus', '0', 0, 0, 0, 0),
(36, 23238, 'Allgemeinwissen1', 'big chungus', '0', 1, 0, 0, 0),
(51, 120939, 'Allgemeinwissen1', 'a', 'a', 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `quizzes`
--

CREATE TABLE `quizzes` (
  `name` text COLLATE utf8_unicode_ci NOT NULL,
  `totalquestions` int(11) NOT NULL,
  `questions` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL CHECK (json_valid(`questions`)),
  `answer1` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL CHECK (json_valid(`answer1`)),
  `answer2` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL CHECK (json_valid(`answer2`)),
  `answer3` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL CHECK (json_valid(`answer3`)),
  `answer4` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL CHECK (json_valid(`answer4`)),
  `rightanswer` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL CHECK (json_valid(`rightanswer`))
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Daten für Tabelle `quizzes`
--

INSERT INTO `quizzes` (`name`, `totalquestions`, `questions`, `answer1`, `answer2`, `answer3`, `answer4`, `rightanswer`) VALUES
('Allgemeinwissen1', 14, '[null,\"Wenn man einen Spiegel mit einem Spiegel spiegelt ist das Spiegelbild in dem Spiegel, mit dem man den Spiegel spiegelt ...\\n\",\"2 * 10^3\\n\",\"Wie hei\\u00dft der Entwickler von C++?\\n\",\"Welcher Berg ist der h\\u00f6chste Berg der Welt?\\n\",\"Wie nennst du ein m\\u00e4nnliches Schwein?\\n\",\"Wie viele Oscars gewann der Film Titanic?\\n\",\"Wie hei\\u00dfen die besten Freunde von \\u201eHarry Potter\\u201c? \\n\",\"Wann wurde Queen Elisabeth II. zur K\\u00f6nigin gekr\\u00f6nt?\\n\",\"Aus wie vielen Einzelknochen besteht eine menschliche Hand? \\n\",\"Was ist ein Sonett?\\n\",\"Wof\\u00fcr stehen die olympischen Ringe? \\n\",\"Wer war der erste Pr\\u00e4sident der Vereinigten Staaten von Amerika?\\n\",\"Wie viele Bundesl\\u00e4nder hat Deutschland?\\n\",\"Wie viele Bundesstaaten hat die USA?\\n\"]', '[null,\"... schwarz\\n\",\"20\\n\",\"Johnny Depp\\n\",\"Mount Everest\\n\",\"Sau\\n\",\"3\\n\",\"Hermine Granger und Ron Weasley\\n\",\"1924\\n\",\"27\\n\",\"Ein Kleid\\n\",\"F\\u00fcr verschiedene Farben\\n\",\"Abraham Lincoln\\n\",\"16\\n\",\"52\\n\"]', '[null,\"... spiegelverkehrt\\n\",\"2000\\n\",\"Mark Zuckerburg\\n\",\"Matterhorn\\n\",\"Schweinchen\\n\",\"5\\n\",\"Hermine Ginger und Ron Waesley\\n\",\"1953\\n\",\"9\\n\",\"Ein Drink\\n\",\"F\\u00fcr die 5 Kontinente\\n\",\"Joe Biden\\n\",\"8\\n\",\"48\\n\"]', '[null,\"... heller\\n\",\"3 * 10^2\\n\",\"Bjarne Stroustrup\\n\",\"Zugspitze\\n\",\"Lamm\\n\",\"11\\n\",\"Elisabeth Granger und Robert Weasley\\n\",\"1963\\n\",\"21\\n\",\"Ein Tanz\\n\",\"F\\u00fcr Audi\\n\",\"George Washington\\n\",\"15\\n\",\"50\\n\"]', '[null,\"... nicht mehr spiegelverkehrt\\n\",\"666\\n\",\"Dennis Ritchie\\n\",\"Lhotse\\n\",\"Eber\\n\",\"1\\n\",\"Elisabeth Ginger und Robert Williams\\n\",\"1939\\n\",\"14\\n\",\"Eine Gedichtform\\n\",\"F\\u00fcr alle\\n\",\"Thomas Jefferson\\n\",\"12\\n\",\"12\\n\"]', '[null,\"4\\n\",\"2\\n\",\"3\\n\",\"1\\n\",\"4\\n\",\"3\\n\",\"1\\n\",\"2\\n\",\"1\\n\",\"4\\n\",\"2\\n\",\"3\\n\",\"1\\n\",\"3\"]'),
('Allgemeinwissen2', 14, '[null,\"Was ist die Hauptstadt von Ghana?\",\"Von wann bis wann dauerte der erste Weltkrieg?\",\"Wann entdeckte Christoph Kolumbus Amerika?\",\"An welchem Datum fiel die Berliner Mauer?\",\"Welches Bundesland ist flu00e4chenmu00e4u00dfig das gru00f6u00dfte?\",\"Wie viele Planeten gehu00f6ren zu unserem Sonnensystem?\",\"Aus wie viel Knochen besteht ein Erwachsenenku00f6rper?\",\"Wie lange hat Goethe an seinem Werk u201eFaustu201c gearbeitet?\",\"Mit wie vielen Figuren startet ein Schachspiel?\",\"Aus was besteht ein Diamant?\",\"Wie lang ist der Panamakanal?\",\"Wie oft finden die Wahlen zum Europu00e4ischen Parlament statt?\",\"Welches Land hat neben der Landessprache 21 anerkannte Sprachen?\",\"Wann bezauberte u201eHarry Potter und der Stein der Weisenu201c weltweit erstmals die Menschen?\"]', '[null,\"New York\",\"1915-1919\",\"1492\",\"9. Dezember 1989\",\"Niedersachsen\",\"6\",\"206\",\"20 Jahre\",\"26\",\"Wasserstoff\",\"82 km\",\"alle Jahre wieder\",\"USA\",\"1999\"]', '[null,\"Accra\",\"1914-1919\",\"1491\",\"9. November 1986\",\"Bayern\",\"10\",\"200\",\"50 Jahre\",\"35\",\"Kohlenstoff\",\"70 km\",\"alle 8 Jahre\",\"Indien\",\"2003\"]', '[null,\"Mexiko\",\"1915-1918\",\"1592\",\"9. November 1989\",\"Mecklenburg-Vorpommern\",\"8\",\"186\",\"64 Jahre\",\"30\",\"Diamantenstoff\",\"85 km\",\"alle 5 Jahre\",\"Nigeria\",\"2001\"]', '[null,\"Accro\",\"1914 u2013 1918\",\"1487\",\"6. November 1989\",\"Saarland\",\"4\",\"260\",\"33 Jahre\",\"32\",\"Stickstoff\",\"67 km\",\"alle 2 Jahre\",\"Schweiz\",\"2005\"]', '[null,\"2\",\"4\",\"1\",\"3\",\"2\",\"3\",\"1\",\"3\",\"4\",\"2\",\"1\",\"3\",\"2\",\"3\"]'),
('Datei Formate', 19, '[null,\".png\",\".mp4\",\".mp3\",\".jpg\",\".mkv\",\".mov\",\".wav\",\".dat\",\".tiff\",\".wma\",\".avi\",\".bmp\",\".gif\",\".ogg\",\".webm\",\".o\",\".a\",\".flac\",\".jar\"]', '[null,\"video\",\"audio\",\"video\",\"video\",\"video\",\"video\",\"video\",\"video\",\"video\",\"video\",\"video\",\"video\",\"video\",\"video\",\"video\",\"video\",\"video\",\"video\",\"video\"]', '[null,\"bild\",\"bild\",\"audio\",\"audio\",\"audio\",\"audio\",\"audio\",\"audio\",\"audio\",\"audio\",\"audio\",\"audio\",\"audio\",\"audio\",\"audio\",\"audio\",\"audio\",\"audio\",\"audio\"]', '[null,\"text\",\"binary\",\"bild\",\"bild\",\"bild\",\"bild\",\"bild\",\"bild\",\"bild\",\"bild\",\"bild\",\"bild\",\"bild\",\"bild\",\"bild\",\"bild\",\"bild\",\"bild\",\"bild\"]', '[null,\"binary\",\"video\",\"binary\",\"binary\",\"binary\",\"binary\",\"binary\",\"binary\",\"binary\",\"binary\",\"binary\",\"binary\",\"binary\",\"binary\",\"binary\",\"binary\",\"binary\",\"binary\",\"binary\"]', '[null,\"2\",\"4\",\"2\",\"3\",\"1\",\"1\",\"2\",\"4\",\"3\",\"2\",\"1\",\"3\",\"3\",\"2\",\"1\",\"4\",\"4\",\"2\",\"4\"]'),
('TestQuiz', 4, '[null,\"1\",\"2\",\"3\",\"4\"]', '[null,\"1\",\"1\",\"1\",\"1\"]', '[null,\"2\",\"2\",\"2\",\"2\"]', '[null,\"3\",\"3\",\"3\",\"3\"]', '[null,\"4\",\"4\",\"4\",\"4\"]', '[null,\"1\",\"2\",\"3\",\"4\"]'),
('irgendwas', 1, '[null,\"wer hat C entwickelt\"]', '[null,\"John Wick\"]', '[null,\"Hans\"]', '[null,\"Dennies Ritchie\"]', '[null,\"ich\"]', '[null,\"3\"]');

--
-- Indizes der exportierten Tabellen
--

--
-- Indizes für die Tabelle `multiplayer`
--
ALTER TABLE `multiplayer`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT für exportierte Tabellen
--

--
-- AUTO_INCREMENT für Tabelle `multiplayer`
--
ALTER TABLE `multiplayer`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=52;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
