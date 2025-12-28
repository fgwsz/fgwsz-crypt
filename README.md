# fgwsz-package
`fgwsz-package`是一个进行打包和解包的工具,
用它打包的包内容使用随机编码混淆.  
```txt
fgwsz-package归档一个或多个(文件/目录)的包标准:
    包的二进制的文件结构如下:
        [file item 1]...[file item N]
    每个文件的二进制信息[file item]的文件结构是[A|B|C|D]:
        A部分是[relative path bytes(8字节)]
        B部分是[relative path]
        C部分是[content bytes(8字节)]
        D部分是[content(binary)]
```
`fgwsz-package`的命令行使用方式如下:  
```txt
Usages:
    Pack  : -c <output package path> <input path 1> ... <input path N>
    Unpack: -x <input package path> <output directory path>
Examples:
    Pack a file and directory: -c mypkg.fgwsz README.md source
    Unpack                   : -x mypkg.fgwsz output
```
