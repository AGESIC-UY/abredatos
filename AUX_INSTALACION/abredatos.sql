-- phpMyAdmin SQL Dump
-- version 3.3.10.4
-- http://www.phpmyadmin.net
--
-- Host: mysql2.municipiomaldonado.gub.uy
-- Generation Time: May 28, 2013 at 01:58 PM
-- Server version: 5.1.53
-- PHP Version: 5.2.17

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `abredatos`
--

-- --------------------------------------------------------

--
-- Table structure for table `abredatos_datasets`
--

CREATE TABLE IF NOT EXISTS `abredatos_datasets` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `DBMS` int(11) NOT NULL,
  `refreshtime` int(6) NOT NULL,
  `description` text,
  `institution` varchar(100) DEFAULT NULL,
  `license` int(11) NOT NULL,
  `category` varchar(100) DEFAULT NULL,
  `lastrun` int(15) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `abredatos_datasets`
--

INSERT INTO `abredatos_datasets` (`id`, `name`, `DBMS`, `refreshtime`, `description`, `institution`, `license`, `category`, `lastrun`) VALUES
(1, 'Prueba real Nomenclator', 5, 1, 'Estos son los datos del Nomenclator Digital del Municipio de Maldonado. Nomenclator Digital es un proyecto cultural y urbano que mantiene una base de datos con el nomenclator de calles, monumentos, sitios historicos de la ciudad. ', 'Municipio de Maldonado', 1, 'cultura', 0);

-- --------------------------------------------------------

--
-- Table structure for table `abredatos_DBMSs`
--

CREATE TABLE IF NOT EXISTS `abredatos_DBMSs` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `driver` int(11) NOT NULL,
  `DBMS_server_URI` varchar(40) NOT NULL,
  `DBMS_TCP_port` int(5) NOT NULL,
  `database_name` varchar(60) NOT NULL,
  `DBMS_username` varchar(40) NOT NULL COMMENT 'CAUTION: create a read-only user for this job',
  `DBMS_password` varchar(40) NOT NULL,
  `comment` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `abredatos_DBMSs`
--

INSERT INTO `abredatos_DBMSs` (`id`, `name`, `driver`, `DBMS_server_URI`, `DBMS_TCP_port`, `database_name`, `DBMS_username`, `DBMS_password`, `comment`) VALUES

(1, 'Prueba Nomenclator ', 5, 'mysql3.municipiomaldonado.gub.uy', 3306, 'nomenclator', 'sql_user', 'XXXXXX', 'este es el comentario de la prueba');

-- --------------------------------------------------------

--
-- Table structure for table `abredatos_drivers`
--

CREATE TABLE IF NOT EXISTS `abredatos_drivers` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(60) NOT NULL,
  `module` varchar(80) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=23 ;

--
-- Dumping data for table `abredatos_drivers`
--

INSERT INTO `abredatos_drivers` (`id`, `name`, `module`) VALUES
(1, 'IBM DB2, interfaz PHP nativa de alta performance', 'db2'),
(2, 'IBM DB2, interfaz ODBC', 'odbc_db2'),
(3, 'FrontBase', 'fbsql'),
(4, 'MySQL - Interfaz tradicional', 'mysql'),
(5, 'MySQL - Nuevo API PHP5 (recomendado)', 'mysqli'),
(6, 'PostgreSQL Driver Generico', 'postgres'),
(7, 'PostgreSQL 6.4 y versiones anteriores', 'postgres64'),
(8, 'PostgreSQL version 7', 'postgres7'),
(9, 'PostgreSQL version 8', 'postgres8'),
(10, 'PostgreSQL version 9', 'postgres9'),
(11, 'Oracle 7', 'oracle'),
(12, 'Oracle 8 y 9 (y versiones posteriores)', 'oci8'),
(13, 'Oracle 8 y 9 (Portable Driver)', 'oci8po'),
(14, 'Microsoft SQL Server', 'mssql'),
(15, 'Microsoft SQL Server (Portable Driver)', 'mssqlpo'),
(16, 'Informix 7.3 y posteriores', 'informix'),
(17, 'Informix 7.2 y anteriores', 'informix72'),
(18, 'SQLite', 'sqlite'),
(19, 'SAP DB', 'sapdb'),
(20, 'Interbase 6 y anteriores', 'ibase'),
(21, 'Sybase', 'sybase'),
(22, 'Firebird', 'firebird');

-- --------------------------------------------------------

--
-- Table structure for table `abredatos_fields`
--

CREATE TABLE IF NOT EXISTS `abredatos_fields` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(60) NOT NULL,
  `dataset` int(11) NOT NULL,
  `EXT_dataset` varchar(50) NOT NULL,
  `DBMS_table_name` varchar(80) NOT NULL,
  `DBMS_field_name` varchar(80) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `abredatos_fields`
--

INSERT INTO `abredatos_fields` (`id`, `name`, `dataset`, `EXT_dataset`, `DBMS_table_name`, `DBMS_field_name`) VALUES
(1, 'campo1', 1, 'Nomenclator Digital', 'campo2', 'campo3'),
(2, 'campo1b', 1, 'Nomenclator Digital', 'campo2', 'campo3b');

-- --------------------------------------------------------

--
-- Table structure for table `abredatos_licenses`
--

CREATE TABLE IF NOT EXISTS `abredatos_licenses` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `comment` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=5 ;

--
-- Dumping data for table `abredatos_licenses`
--

INSERT INTO `abredatos_licenses` (`id`, `name`, `comment`) VALUES
(1, 'GNU GPL Version 3', 'Esta licencia garantiza a los usuarios finales, estos sean personas, organizaciones, compani­as, la libertad de usar, estudiar, compartir, copiar y modificar la obra, en tanto se siga distribuyendo bajo la misma licencia. Mas informacion en http://www.gnu.org/licenses/'),
(2, 'Creative Commons 3.0', 'Esta licencia permite a otros distribuir, remezclar, retocar, y crear a partir de una obra, incluso con fines comerciales, siempre y cuando se den credito por la creacion original. Se recomienda para la maxima difusion y utilizacion de los materiales licenciados.\r\nMas informacion en:  http://creativecommons.org/licenses/'),
(3, 'Open Database License (ODbL)', 'Esta licencia es orientada a bases de datos, la cual permite copiar, distribuir, remezclar, modificar y crear a partir de dicha obra, incluso con fines comerciales, siempre y cuando se den creditos a la fuente creadora y se mantenga la misma licencia para cualquier obra derivada. Mas informacion en http://opendatacommons.org/licenses/odbl/summary/'),
(4, 'OpenContent License (OPL)', 'La Open Content License (OPL) es una licencia de contenido abierto creada en 1998. Es una de las primeras que no fue pensada originalmente para software libre, sino para contenidos y datos.\r\nContiene un copyleft fuerte, obras derivadas deben ser publicadas bajo la misma licencia.  Mas informacion en http://opencontent.org/opl.shtml');

-- --------------------------------------------------------

--
-- Table structure for table `acl_groups`
--

CREATE TABLE IF NOT EXISTS `acl_groups` (
  `name` varchar(20) NOT NULL,
  `description` varchar(100) DEFAULT NULL,
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `acl_groups`
--

INSERT INTO `acl_groups` (`name`, `description`) VALUES
('abredatos_admin', 'manage Abredatos'),
('admin', 'can do everything');

-- --------------------------------------------------------

--
-- Table structure for table `acl_groups2res`
--

CREATE TABLE IF NOT EXISTS `acl_groups2res` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `group` varchar(20) NOT NULL,
  `module` varchar(60) NOT NULL COMMENT 'resource is: module/operation',
  `operation` varchar(30) NOT NULL COMMENT 'resource is: module/operation',
  `negative` tinyint(1) NOT NULL DEFAULT '0',
  `menu_group` varchar(65) DEFAULT NULL,
  `menu_caption` varchar(65) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=16 ;

--
-- Dumping data for table `acl_groups2res`
--

INSERT INTO `acl_groups2res` (`id`, `group`, `module`, `operation`, `negative`, `menu_group`, `menu_caption`) VALUES
(1, 'abredatos_admin', 'abredatos', 'index', 0, NULL, NULL),
(2, 'abredatos_admin', 'abredatos', 'DBMSs', 0, 'Administracion de ABREDATOS', 'Conexiones DBMS'),
(3, 'abredatos_admin', 'abredatos', 'DBMSs_c', 0, NULL, NULL),
(4, 'abredatos_admin', 'abredatos', 'DBMSs_f', 0, NULL, NULL),
(5, 'abredatos_admin', 'abredatos', 'DBMSs_d', 0, NULL, NULL),
(6, 'abredatos_admin', 'abredatos', 'licenses', 0, 'Administracion de ABREDATOS', 'Tipos de Licencias'),
(7, 'abredatos_admin', 'abredatos', 'licenses_c', 0, NULL, NULL),
(8, 'abredatos_admin', 'abredatos', 'licenses_d', 0, NULL, NULL),
(9, 'abredatos_admin', 'abredatos', 'datasets', 0, 'Administracion de ABREDATOS', 'Administrar Datasets'),
(10, 'abredatos_admin', 'abredatos', 'datasets_c', 0, NULL, NULL),
(11, 'abredatos_admin', 'abredatos', 'datasets_f', 0, NULL, NULL),
(12, 'abredatos_admin', 'abredatos', 'datasets_d', 0, NULL, NULL),
(13, 'abredatos_admin', 'abredatos', 'campos', 0, 'Administracion de ABREDATOS', 'Campos de datos'),
(14, 'abredatos_admin', 'abredatos', 'campos_c', 0, NULL, NULL),
(15, 'abredatos_admin', 'abredatos', 'campos_d', 0, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `acl_metagroups`
--

CREATE TABLE IF NOT EXISTS `acl_metagroups` (
  `name` varchar(20) NOT NULL,
  `description` varchar(100) DEFAULT NULL,
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `acl_metagroups`
--


-- --------------------------------------------------------

--
-- Table structure for table `acl_metagroups2groups`
--

CREATE TABLE IF NOT EXISTS `acl_metagroups2groups` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `metagroup` varchar(20) NOT NULL,
  `group` varchar(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- Dumping data for table `acl_metagroups2groups`
--


-- --------------------------------------------------------

--
-- Table structure for table `acl_users`
--

CREATE TABLE IF NOT EXISTS `acl_users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(20) NOT NULL,
  `cryptpass` varchar(40) NOT NULL,
  `realname` varchar(40) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `acl_users`
--

INSERT INTO `acl_users` (`id`, `username`, `cryptpass`, `realname`) VALUES
(1, 'eduardo', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Ing. Eduardo Gonzalez'),
(2, 'irismontesdeoca', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Iris Montes de Oca');

-- --------------------------------------------------------

--
-- Table structure for table `acl_users2groups`
--

CREATE TABLE IF NOT EXISTS `acl_users2groups` (
  `user` int(11) NOT NULL,
  `group` varchar(20) NOT NULL,
  KEY `user` (`user`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `acl_users2groups`
--

INSERT INTO `acl_users2groups` (`user`, `group`) VALUES
(1, 'abredatos_admin'),
(2, 'abredatos_admin');

-- --------------------------------------------------------

--
-- Table structure for table `acl_users2metagroups`
--

CREATE TABLE IF NOT EXISTS `acl_users2metagroups` (
  `user` int(11) NOT NULL,
  `metagroup` varchar(20) NOT NULL,
  KEY `user` (`user`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `acl_users2metagroups`
--



-- --------------------------------------------------------

--
-- Table structure for table `log`
--

CREATE TABLE IF NOT EXISTS `log` (
  `datetime` datetime NOT NULL,
  `ip` varchar(46) NOT NULL,
  `xforwardedf` varchar(46) DEFAULT NULL,
  `useragent` text NOT NULL,
  `userid` int(11) NOT NULL,
  `event` varchar(15) NOT NULL,
  `details` text,
  PRIMARY KEY (`datetime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `log`
--

INSERT INTO `log` (`datetime`, `ip`, `xforwardedf`, `useragent`, `userid`, `event`, `details`) VALUES
('2013-05-12 19:31:24', '190.135.184.137', '', 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:16.0) Gecko/20100101 Firefox/16.0', 2, 'LOGINOK', 'username: irismontesdeoca');

