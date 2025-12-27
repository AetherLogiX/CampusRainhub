-- 嗯，放个脚本专门用来删数据库吧，因为经常搞错
drop database if exists rainhub_db;
-- 检测是否成功删除
select 'drop_db.sql drop database successfully!' as message;