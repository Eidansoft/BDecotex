-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u1
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tiempo de generación: 11-08-2016 a las 19:29:28
-- Versión del servidor: 5.5.49-0+deb8u1
-- Versión de PHP: 5.6.22-0+deb8u1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de datos: `bdecotex`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `family`
--

CREATE TABLE IF NOT EXISTS `family` (
`id_family` int(11) NOT NULL COMMENT 'Id',
  `description` varchar(100) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Description',
  `code` varchar(50) COLLATE utf8_unicode_ci NOT NULL COMMENT 'The code to identify the family and use it at composition for model code'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Family products';

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `family`
--
ALTER TABLE `family`
 ADD PRIMARY KEY (`id_family`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `family`
--
ALTER TABLE `family`
MODIFY `id_family` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Id';
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
