-- phpMyAdmin SQL Dump
-- version 4.9.5
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Feb 29, 2024 at 11:29 PM
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
-- Table structure for table `kundebehandler`
--

CREATE TABLE `kundebehandler` (
  `KundebehandlerNr` int(11) NOT NULL,
  `KundebehandlerNavn` varchar(50) NOT NULL,
  `KundebehandlerInitialer` varchar(3) NOT NULL,
  `KundebehandlerTlf` varchar(9) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `kundebehandler`
--

INSERT INTO `kundebehandler` (`KundebehandlerNr`, `KundebehandlerNavn`, `KundebehandlerInitialer`, `KundebehandlerTlf`) VALUES
(1, 'Hilde Pettersen', 'HPE', '10090999'),
(2, 'Berit Hansen', 'BHA', '10191999'),
(3, 'Hans Hansen', 'HHA', '10291999');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `kundebehandler`
--
ALTER TABLE `kundebehandler`
  ADD PRIMARY KEY (`KundebehandlerNr`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `kundebehandler`
--
ALTER TABLE `kundebehandler`
  MODIFY `KundebehandlerNr` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
