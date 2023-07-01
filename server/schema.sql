CREATE DATABASE IF NOT EXISTS microcontroller;
USE microcontroller;

DROP TABLE IF EXISTS `microcontroller`;

CREATE TABLE IF NOT EXISTS `microcontroller` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `temperature` varchar(255) NOT NULL,
  `distance` varchar(255) NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `microcontroller` (`id`, `temperature`, `distance`) VALUES
(1, '0', '0');