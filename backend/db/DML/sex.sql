-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u1
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tiempo de generación: 19-06-2016 a las 16:58:43
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
-- Estructura de tabla para la tabla `sex`
--

CREATE TABLE IF NOT EXISTS `sex` (
`id_sex` int(11) NOT NULL COMMENT 'Sex id',
  `name` varchar(50) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Name: Hombre, Mujer, Embarazada, ...',
  `code` varchar(2) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Code to represent the sex, H for Hombre, M for Mujer, E for Embarazada'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Sex codes table';

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `sex`
--
ALTER TABLE `sex`
 ADD PRIMARY KEY (`id_sex`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `sex`
--
ALTER TABLE `sex`
MODIFY `id_sex` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Sex id';
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
