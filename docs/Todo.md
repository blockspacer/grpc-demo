# 安全性
1. XSS过滤
2. SQL注入防范
    - mysql-connector-c++可以使用prepared statement来执行SQL语句
3. 密码存储
    - 当前只使用了md5加盐，为提高安全性，应考虑混合加密的方式