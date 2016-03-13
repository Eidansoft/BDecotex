-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u1
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tiempo de generación: 13-03-2016 a las 05:28:02
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
  `front` varchar(500) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Front description',
  `back` varchar(500) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Back information',
  `neck` varchar(500) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Neck description',
  `arm` varchar(500) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Arm description',
  `observations` varchar(500) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Other observations',
  `old_model_number` varchar(50) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Old model number reference',
  `xid_model_parent` int(11) DEFAULT NULL COMMENT 'Base pattern',
  `creation_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'Creation date',
  `variant` int(11) NOT NULL,
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
