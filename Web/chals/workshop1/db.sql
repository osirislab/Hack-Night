CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `username` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

INSERT INTO `users` (`id`, `username`, `password`) VALUES
(1, 'admin', SHA1('C0rr3ctH0rseB@tt3rySt@p1e'));

ALTER TABLE `users`
 ADD PRIMARY KEY (`id`);
