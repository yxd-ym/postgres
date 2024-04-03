CREATE EXTENSION test_lfind;

--
-- These tests don't produce any interesting output.  We're checking that
-- the operations complete without crashing or hanging and that none of their
-- internal sanity tests fail.
--
SELECT test_lfind8();
SELECT test_lfind8_le();
SELECT test_lfind32();

\timing on
SELECT drive_lfind32(0);
SELECT drive_lfind32(1);
SELECT drive_lfind32(2);
SELECT drive_lfind32(3);
SELECT drive_lfind32(4);
SELECT drive_lfind32(5);
SELECT drive_lfind32(6);
SELECT drive_lfind32(7);
SELECT drive_lfind32(8);
SELECT drive_lfind32(9);
SELECT drive_lfind32(10);
SELECT drive_lfind32(11);
SELECT drive_lfind32(12);
SELECT drive_lfind32(13);
SELECT drive_lfind32(14);
SELECT drive_lfind32(15);
SELECT drive_lfind32(16);
SELECT drive_lfind32(17);
SELECT drive_lfind32(18);
SELECT drive_lfind32(19);
SELECT drive_lfind32(20);
SELECT drive_lfind32(21);
SELECT drive_lfind32(22);
SELECT drive_lfind32(23);
SELECT drive_lfind32(24);
SELECT drive_lfind32(25);
SELECT drive_lfind32(26);
SELECT drive_lfind32(27);
SELECT drive_lfind32(28);
SELECT drive_lfind32(29);
SELECT drive_lfind32(30);
SELECT drive_lfind32(31);
SELECT drive_lfind32(32);
SELECT drive_lfind32(33);
SELECT drive_lfind32(34);
SELECT drive_lfind32(35);
SELECT drive_lfind32(36);
SELECT drive_lfind32(37);
SELECT drive_lfind32(38);
SELECT drive_lfind32(39);
SELECT drive_lfind32(40);
SELECT drive_lfind32(41);
SELECT drive_lfind32(42);
SELECT drive_lfind32(43);
SELECT drive_lfind32(44);
SELECT drive_lfind32(45);
SELECT drive_lfind32(46);
SELECT drive_lfind32(47);
SELECT drive_lfind32(48);
SELECT drive_lfind32(49);
SELECT drive_lfind32(50);
SELECT drive_lfind32(51);
SELECT drive_lfind32(52);
SELECT drive_lfind32(53);
SELECT drive_lfind32(54);
SELECT drive_lfind32(55);
SELECT drive_lfind32(56);
SELECT drive_lfind32(57);
SELECT drive_lfind32(58);
SELECT drive_lfind32(59);
SELECT drive_lfind32(60);
SELECT drive_lfind32(61);
SELECT drive_lfind32(62);
SELECT drive_lfind32(63);
SELECT drive_lfind32(64);
