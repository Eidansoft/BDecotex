-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u1
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tiempo de generación: 06-03-2016 a las 20:04:04
-- Versión del servidor: 5.5.46-0+deb8u1
-- Versión de PHP: 5.6.14-0+deb8u1

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
-- Estructura de tabla para la tabla `model`
--

CREATE TABLE IF NOT EXISTS `model` (
`id_model` int(11) NOT NULL COMMENT 'Model ID',
  `description` varchar(1000) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Model description',
  `model_number` varchar(50) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Model number',
  `tallaje` varchar(100) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Sizes avaiable',
  `patron_base` varchar(100) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Base pattern',
  `xid_family` int(11) NOT NULL COMMENT 'Family',
  `xid_line` int(11) NOT NULL COMMENT 'Line',
  `xid_sex` int(11) NOT NULL COMMENT 'Sex'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Models table';

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `model`
--
ALTER TABLE `model`
 ADD PRIMARY KEY (`id_model`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `model`
--
ALTER TABLE `model`
MODIFY `id_model` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Model ID';
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
