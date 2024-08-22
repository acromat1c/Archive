-- phpMyAdmin SQL Dump
-- version 4.9.5
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Feb 29, 2024 at 06:29 PM
-- Server version: 10.5.18-MariaDB
-- PHP Version: 7.4.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `stud_v24_ilres6917`
--

-- --------------------------------------------------------

--
-- Table structure for table `utstyr`
--

CREATE TABLE `utstyr` (
  `UtstyrsID` varchar(11) NOT NULL,
  `Type` varchar(50) NOT NULL,
  `Merke` varchar(50) NOT NULL,
  `Modell` varchar(50) NOT NULL,
  `Beskrivelse` varchar(250) NOT NULL,
  `Kategori` varchar(50) NOT NULL,
  `Leiepris` int(11) NOT NULL,
  `Antall` int(11) NOT NULL,
  `VedlikeholdtInterval` varchar(25) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `utstyr`
--

INSERT INTO `utstyr` (`UtstyrsID`, `Type`, `Merke`, `Modell`, `Beskrivelse`, `Kategori`, `Leiepris`, `Antall`, `VedlikeholdtInterval`) VALUES
('1001', 'Minigraver', 'Hitachi', 'ZX10U-6', 'Minigraveren ZX10U-6 fra Hitachi er vår minste minigraver og er laget for bruk på trange og små plasser', 'Tunge maskiner', 1200, 1, '3 år'),
('233', 'Kompressor', 'Stanley', 'Vento 6L', 'Liten og hendig, med en motor på 1,5HK. Regulerbart trykk opp till 8bar, 180L luft i minuttet. ', 'Lette maskiner', 79, 10, '3 år'),
('234', 'Spikerpistol', 'ESSVE', 'Coil CN-15-65', 'ESSVE Coilpistol beregnet for spikring av bjelkelag, reisverk, kledning, utforinger, panel, sponplater m.m. Smidig spikerpistol med maskinkropp i magnesium, justerbart utblås og beltekrok.', 'Lette maskiner', 100, 50, '1 år'),
('7653', 'Stilas', 'Haki Stilas', '150', 'Stilas på ca 150 kvadratmeter.', 'Annleggsutstyr', 350, 2, '5 år'),
('7654', 'Sementblander', 'Atika', '130l 600w', 'Atika betongblander med kapasitet på 130 l og 600 W. Bruker 230 V. IP44', 'Annleggsutstyr', 230, 8, '5 år');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `utstyr`
--
ALTER TABLE `utstyr`
  ADD PRIMARY KEY (`UtstyrsID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
