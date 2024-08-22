-- phpMyAdmin SQL Dump
-- version 4.9.5
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3306
-- Generation Time: Feb 29, 2024 at 06:28 PM
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
-- Table structure for table `orders`
--

CREATE TABLE `orders` (
  `OrderID` int(11) NOT NULL,
  `KundeNr` int(11) NOT NULL,
  `KundebehandlerNr` int(11) NOT NULL,
  `UtstyrsID` int(11) NOT NULL,
  `InstansID` int(11) NOT NULL,
  `UtleidDato` date NOT NULL,
  `InnlevertDato` date DEFAULT NULL,
  `Betaling` varchar(10) NOT NULL,
  `LeveresKunde` varchar(3) NOT NULL,
  `LeveringsKostnad` decimal(11,2) DEFAULT NULL,
  `Betalt` decimal(11,2) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Dumping data for table `orders`
--

INSERT INTO `orders` (`OrderID`, `KundeNr`, `KundebehandlerNr`, `UtstyrsID`, `InstansID`, `UtleidDato`, `InnlevertDato`, `Betaling`, `LeveresKunde`, `LeveringsKostnad`, `Betalt`) VALUES
(1, 20011, 1, 233, 1, '2021-02-01', NULL, 'Kort', 'ja', '150.00', NULL),
(2, 10002, 1, 1001, 1, '2021-02-05', '2021-02-08', 'Kontant', 'ja', '500.00', '4100.00'),
(3, 11122, 2, 7653, 1, '2021-02-05', NULL, 'Kort', 'nei', NULL, NULL),
(4, 8988, 2, 7654, 1, '2020-02-04', '2020-02-10', 'Vipps', 'ja', '200.00', '1580.00'),
(5, 20011, 2, 233, 2, '2019-03-05', '2019-03-06', 'Kontant', 'nei', NULL, '79.00'),
(6, 11122, 3, 234, 1, '2019-02-01', '2019-02-03', 'Kort', 'nei', NULL, '200.00');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `orders`
--
ALTER TABLE `orders`
  ADD PRIMARY KEY (`OrderID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `orders`
--
ALTER TABLE `orders`
  MODIFY `OrderID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
