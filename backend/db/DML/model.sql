-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u1
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tiempo de generación: 10-08-2016 a las 22:35:45
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
-- Estructura de tabla para la tabla `model`
--

CREATE TABLE IF NOT EXISTS `model` (
`id_model` int(11) NOT NULL COMMENT 'Model ID',
  `xid_family` int(11) NOT NULL COMMENT 'Family',
  `xid_line` int(11) NOT NULL COMMENT 'Line',
  `xid_sex` int(11) NOT NULL COMMENT 'Sex',
  `variant` int(11) NOT NULL COMMENT 'Secuence to identify de model',
  `description` varchar(1000) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Model description',
  `front` varchar(500) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Front description',
  `back` varchar(500) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Back information',
  `neck` varchar(500) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Neck description',
  `arm` varchar(500) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Arm description',
  `observations` varchar(500) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Other observations',
  `model_number_parent` varchar(50) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Old reference to parent model not stored at DB. For historic porpouses',
  `xid_model_parent` int(11) DEFAULT NULL COMMENT 'Base pattern. In case the old reference exists at this DB',
  `creation_date` int(11) NOT NULL COMMENT 'Creation date',
  `client` varchar(50) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'End client name, the model was created for.',
  `old_ref` varchar(50) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'Old reference. Stored for historic porpouses because the reference must be the union of Family+Line+Sex+Variant'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Models table. The complete human readable identification for the model is the union of Family+Line+Sex+Variant';

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
