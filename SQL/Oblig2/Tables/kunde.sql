-- phpMyAdmin SQL Dump
-- version 4.9.5
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Mar 01, 2024 at 11:15 AM
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
-- Table structure for table `kunde`
--

CREATE TABLE `kunde` (
  `KundeNr` int(11) NOT NULL,
  `Navn` varchar(50) NOT NULL,
  `Type` varchar(10) NOT NULL,
  `Telefonnr1` varchar(12) NOT NULL,
  `Telefonnr2` varchar(12) DEFAULT NULL,
  `Telefonnr3` varchar(12) DEFAULT NULL,
  `Epost` varchar(50) NOT NULL,
  `FakturaAdrGate` varchar(50) NOT NULL,
  `FakturaAdrGateNr` int(11) NOT NULL,
  `FakturaAdrPostNr` varchar(4) NOT NULL,
  `LeveringsAdrGate` varchar(50) NOT NULL,
  `LeveringsAdrGateNr` int(11) NOT NULL,
  `LeveringsAdrPostNr` varchar(4) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `kunde`
--

INSERT INTO `kunde` (`KundeNr`, `Navn`, `Type`, `Telefonnr1`, `Telefonnr2`, `Telefonnr3`, `Epost`, `FakturaAdrGate`, `FakturaAdrGateNr`, `FakturaAdrPostNr`, `LeveringsAdrGate`, `LeveringsAdrGateNr`, `LeveringsAdrPostNr`) VALUES
(8988, 'Murer Pedersen ANS', 'Bedrift', '90099888', '', '', 'mu_pe@ånnlain.no', 'Murergata', 1, '9001', 'Murergata', 2, '9000'),
(10002, 'Grøft og Kant AS', 'Bedrift', '769000111', '99988877', '', 'gm@uuiitt.nu', 'Øvregata', 332, '8001', 'Lillegata', 233, '8000'),
(11122, 'Lokalbyggern AS', 'Bedrift', '7766554', '', '', 'lok_bygg@no.no', 'Nedreveien', 223, '8000', 'Veien', 124, '8000'),
(20011, 'Anders Andersen', 'Privat', '76900112', '99988777', '22122333', 'aa@post.no', 'Fjelltoppen', 4, '8501', 'Fjelltoppen', 3, '8500');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `kunde`
--
ALTER TABLE `kunde`
  ADD PRIMARY KEY (`KundeNr`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
