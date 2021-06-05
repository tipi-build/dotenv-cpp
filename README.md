# dotenv-cpp

Simple helper library.
You can just compile with nxxm without any dependencies
This library is cross-platform and without dependency

## How it works 
You can use the main function as follows 
```
doting::use_dotenv_file( path_filename,preserve )
```

If preserve is true then if your environment file then if you already have environment values they will not be overwrite.
And for path_filename give it a string which contains the path of your environment file.

If you want to test my program with the test program just remember to change the path to the file 

## Usage
[Simply use via nxxm](https://nxxm.github.io/), `.nxxm/deps` file : 
```
{
  "lambourl/dotenv-cpp" : {"@" : "main"}
}
```

```
Copyright (c) 2021 Luc Lambour alias Lambourl (lmbrluc@gmail.com)
```
