-- phpMyAdmin SQL Dump
-- version 4.2.12deb2+deb8u1
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tiempo de generación: 06-03-2016 a las 20:03:58
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
-- Estructura de tabla para la tabla `message`
--

CREATE TABLE IF NOT EXISTS `message` (
`id_message` int(11) NOT NULL COMMENT 'Message id',
  `desc_message` varchar(100) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Default message description',
  `type_message` varchar(3) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Message type. One option between INF, WAR and ERR'
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Messages table';

--
-- Volcado de datos para la tabla `message`
--

INSERT INTO `message` (`id_message`, `desc_message`, `type_message`) VALUES
(1, 'Can''t connect to database', 'ERR'),
(2, 'SQL query with error', 'ERR'),
(3, 'Resource not found', 'ERR'),
(4, 'Param not valid', 'ERR'),
(5, 'Unkown error', 'ERR');

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `message`
--
ALTER TABLE `message`
 ADD PRIMARY KEY (`id_message`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `message`
--
ALTER TABLE `message`
MODIFY `id_message` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Message id',AUTO_INCREMENT=6;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
