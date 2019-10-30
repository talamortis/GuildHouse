-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               5.6.28 - MySQL Community Server (GPL)
-- Server OS:                    Win64
-- HeidiSQL Version:             9.4.0.5125
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- Dumping structure for table acore_char.guild_house
CREATE TABLE IF NOT EXISTS `guild_house` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `guild` int(11) NOT NULL DEFAULT '0',
  `phase` int(11) NOT NULL,
  `map` int(11) NOT NULL DEFAULT '0',
  `positionX` float NOT NULL DEFAULT '0',
  `positionY` float NOT NULL DEFAULT '0',
  `positionZ` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `guild` (`guild`)
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=utf8;

-- Dumping data for table acore_char.guild_house: ~2 rows (approximately)
/*!40000 ALTER TABLE `guild_house` DISABLE KEYS */;
REPLACE INTO `guild_house` (`id`, `guild`, `phase`, `map`, `positionX`, `positionY`, `positionZ`) VALUES
	(19, 1, 1, 1, 16226.1, 16258, 13.2576),
	(23, 2, 2, 1, 16226.1, 16258, 13.2576);
/*!40000 ALTER TABLE `guild_house` ENABLE KEYS */;

-- Dumping structure for table acore_world.guild_house_spawns
CREATE TABLE IF NOT EXISTS `guild_house_spawns` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `entry` int(11) NOT NULL DEFAULT '0',
  `posX` float NOT NULL DEFAULT '0',
  `posY` float NOT NULL DEFAULT '0',
  `posZ` float NOT NULL DEFAULT '0',
  `orientation` float NOT NULL DEFAULT '0',
  `comment` varchar(500) DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `entry` (`entry`)
) ENGINE=InnoDB AUTO_INCREMENT=51 DEFAULT CHARSET=utf8;

-- Dumping data for table acore_world.guild_house_spawns: ~56 rows (approximately)
/*!40000 ALTER TABLE `guild_house_spawns` DISABLE KEYS */;
REPLACE INTO `guild_house_spawns` (`id`, `entry`, `posX`, `posY`, `posZ`, `orientation`, `comment`) VALUES
	(1, 26327, 16216.5, 16279.4, 20.9306, 0.552869, 'Paladin Trainer'),
	(2, 26324, 16221.3, 16275.7, 20.9285, 1.37363, 'Druid Trainer'),
	(3, 26325, 16218.6, 16277, 20.9872, 0.967188, 'Hunter Trainer'),
	(4, 26326, 16224.9, 16274.9, 20.9319, 1.58765, 'Mage Trainer'),
	(5, 26328, 16227.9, 16275.9, 20.9254, 1.9941, 'Priest Trainer'),
	(6, 26329, 16231.4, 16278.1, 20.9222, 2.20026, 'Rogue Trainer'),
	(7, 26330, 16235.5, 16280.8, 20.9257, 2.18652, 'Shaman Trainer'),
	(8, 26331, 16240.8, 16283.3, 20.9299, 1.86843, 'Warlock Trainer'),
	(9, 26332, 16246.6, 16284.5, 20.9301, 1.68975, 'Warrior Trainer'),
	(10, 18649, 16224.1, 16284.2, 13.1755, 4.65225, 'Inkeeper'),
	(11, 30605, 16238.2, 16291.8, 22.9306, 1.55386, 'Banker'),
	(12, 33251, 16252.3, 16284.9, 20.9324, 1.79537, 'Death Knight Trainer'),
	(13, 33609, 16220.5, 16302.3, 13.176, 6.14647, 'Blacksmithing Trainer'),
	(14, 33617, 16220.2, 16299.6, 13.178, 6.22894, 'Mining Trainer'),
	(15, 33611, 16219.8, 16296.9, 13.1746, 6.24465, 'Engineering Trainer'),
	(16, 33614, 16222.4, 16293, 13.1813, 1.51263, 'Jewelcrafting Trainer'),
	(17, 33610, 16227.5, 16292.3, 13.1839, 1.49691, 'Enchanting Trainer'),
	(18, 33615, 16231.6, 16301, 13.1757, 3.07372, 'Inscription Trainer'),
	(19, 33612, 16231.2, 16295, 13.1761, 3.06574, 'Leatherworking Trainer'),
	(20, 33618, 16228.9, 16304.7, 13.1819, 4.64831, 'Skinning Trainer'),
	(21, 33608, 16218.1, 16281.8, 13.1756, 6.1975, 'Alchemy Trainer'),
	(22, 33616, 16218.3, 16284.3, 13.1756, 6.1975, 'Herbalism Trainer'),
	(23, 33613, 16220.4, 16278.7, 13.1756, 1.46157, 'Tailoring Trainer'),
	(24, 33621, 16225, 16310.9, 29.262, 6.22119, 'First Aid Trainer'),
	(25, 33623, 16225.3, 16313.9, 29.262, 6.28231, 'Fishing Trainer'),
	(26, 33619, 16227, 16278, 13.1762, 1.4872, 'Cooking Trainer'),
	(27, 8719, 16242, 16291.6, 22.9311, 1.52061, 'Alliance Auctioneer'),
	(30, 9856, 16242, 16291.6, 22.9311, 1.52061, 'Horde Auctioneer'),
	(31, 184137, 16220.3, 16272, 12.9736, 4.45592, 'Mailbox (Object)'),
	(33, 1685, 16253.8, 16294.3, 13.1758, 6.11938, 'Forge (Object)'),
	(34, 4087, 16254.4, 16298.7, 13.1758, 3.36027, 'Anvil (Object)'),
	(36, 183325, 16214.8, 16218, 1.11903, 1.35357, 'Portal: Stormwind (Object)'),
	(37, 183323, 16214.8, 16218, 1.11903, 1.35357, 'Portal: Orgrimmar (Object)'),
	(38, 183322, 16222.8, 16216.9, 1.22016, 1.57937, 'Portal: Ironforge (Object)'),
	(39, 183327, 16222.8, 16216.9, 1.22016, 1.57937, 'Portal: Undercity (Object)'),
	(40, 183317, 16202.1, 16223.1, 1.03401, 0.829316, 'Portal: Darnassus (Object)'),
	(41, 183326, 16202.1, 16223.1, 1.03401, 0.829316, 'Portal: Thunder Bluff (Object)'),
	(42, 183324, 16196.8, 16227.5, 1.37206, 0.762557, 'Portal: Silvermoon (Object)'),
	(43, 183321, 16196.8, 16227.5, 1.37206, 0.762557, 'Portal: Exodar (Object)'),
	(44, 195682, 16207, 16216, 1.10669, 1.0453, 'Portal: Dalaran (Object)'),
	(45, 187293, 16230.5, 16283.5, 13.9061, 3, 'Guild Vault (Object)'),
	(46, 28692, 16230.2, 16316.4, 20.8455, 6.25643, 'Trade Supplies'),
	(48, 28776, 16236.3, 16316.1, 20.8454, 3.06771, 'Tabard Vendor'),
	(49, 70103, 16223.7, 16293.3, 20.852, 4.57958, 'Food & Drink'),
    (50, 6491, 16319.937, 16242.404, 24.4747, 2.206830, 'Spirit Healer'),
    (51, 191028, 16255.5, 16304.9, 20.9785, 2.97516, 'Barber Chair (Object)'),
    (52, 191013, 16203, 16216, 1.10669, 1.0453, 'Portal: Shattrath (Object) - Alliance'),
    (53, 29636, 16233.5, 16316.1, 20.8455, 3.07558, 'Reagent Vendor'),
    (54, 191014, 16203, 16216, 1.10669, 1.0453, 'Portal: Shattrath (Object) - Horde'),
    (55, 70104, 16242.8, 16302.1, 13.174, 4.6153, 'Ammo & Repair Vendor'),
    (56, 28690, 16226.97, 16267.9, 13.15, 4.6533, 'Stable Master');
	
/*!40000 ALTER TABLE `guild_house_spawns` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
