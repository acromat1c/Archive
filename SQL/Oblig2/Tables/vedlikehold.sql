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
-- Table structure for table `vedlikehold`
--

CREATE TABLE `vedlikehold` (
  `VedlikeholdtNr` int(11) NOT NULL,
  `UtstyrsID` int(11) NOT NULL,
  `InstansID` int(11) NOT NULL,
  `UtstyrVedlikeholdtDato` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `vedlikehold`
--

INSERT INTO `vedlikehold` (`VedlikeholdtNr`, `UtstyrsID`, `InstansID`, `UtstyrVedlikeholdtDato`) VALUES
(1, 233, 1, '2018-04-03'),
(2, 1001, 1, '2019-09-01'),
(3, 7653, 1, '2016-12-11'),
(4, 7654, 1, '2019-03-20'),
(5, 233, 2, '2017-01-02'),
(6, 234, 1, '2021-02-10');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `vedlikehold`
--
ALTER TABLE `vedlikehold`
  ADD PRIMARY KEY (`VedlikeholdtNr`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `vedlikehold`
--
ALTER TABLE `vedlikehold`
  MODIFY `VedlikeholdtNr` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
