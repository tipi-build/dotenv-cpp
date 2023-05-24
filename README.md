# dotenv-cpp

Simple helper library.
You can just compile with tipi without any dependencies
This library is cross-platform and without dependency

## How it works 
You can use the struct as follows 

```
dotenv::Myenv Env_app( env_map, path_filename, preserve )
Env_app.use_dotenv_file();
```

If preserve is true then if your environment file then if you already have environment values they will not be overwrite.
And for maps is an std::map<std::string,std::string>  which contains some environement variable.
And for path_filename give it a string which contains the path of your environment file.
This lib can support multi-line but on some condition you must have a multiline with a value that starts and ends with "
for example for multi-line :

```
KEYSSH="-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAABG5vbmUAAAAEbm9uZQAAAAAAAAABAAACFwAAAAdzc2gtcn
WKbxW+yHb//5AAAAFWx1Y2xhbWJvdXJATUJQLWRlLUx1YwECAwQF
-----END OPENSSH PRIVATE KEY-----"
```
If you want to test my program with the test program just remember to change the path to the file 

## Usage
[Simply use via tipi.build](https://tipi.build), `.tipi/deps` file : 
```
{
  "lambourl/dotenv-cpp" : {"@" : "main"}
}
```

```
Copyright (c) 2021 Luc Lambour alias Lambourl (lmbrluc@gmail.com)
```
