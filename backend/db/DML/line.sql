-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u1
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tiempo de generación: 19-06-2016 a las 18:49:45
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
-- Estructura de tabla para la tabla `line`
--

CREATE TABLE IF NOT EXISTS `line` (
`id_line` int(11) NOT NULL COMMENT 'id line',
  `name` varchar(50) COLLATE utf8_unicode_ci NOT NULL COMMENT 'line name'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Line table for each different line';

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `line`
--
ALTER TABLE `line`
 ADD PRIMARY KEY (`id_line`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `line`
--
ALTER TABLE `line`
MODIFY `id_line` int(11) NOT NULL AUTO_INCREMENT COMMENT 'id line';
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
