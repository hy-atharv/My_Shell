# MY SHELL
### Basic Unix/Linux Shell implementation in C 

### ⚙️Features

- **Written in C**

- **Supports all general POSIX commands**

- **Handles improper space in commands**

- **Supports Piping**

- **Runs in both Unix and Linux based operating systems**





<img width="500" src="https://github.com/user-attachments/assets/4a5e8f02-dc86-4a4d-92c8-09e69d50af84" />

***MY SHELL in WSL(Windows Subsystem for Linux)***


<img width="500" src="https://github.com/user-attachments/assets/b515b761-c6fb-4d50-8cca-8ac61f00664b" />

***MY SHELL in macOS***


### 💻Executing in Linux based systems

**1. Install the readline library by GNU**

```
sudo apt-get install libreadline-dev
```

**2. Download the [myshell.c](https://github.com/hy-atharv/My_Shell/blob/9e532c6a52e195d55d067411fdec83055ecee1e7/myshell.c)**

**3. Navigate to the directory where you downloaded [myshell.c](https://github.com/hy-atharv/My_Shell/blob/9e532c6a52e195d55d067411fdec83055ecee1e7/myshell.c)**

**4. Link the readline library and compile the [myshell.c](https://github.com/hy-atharv/My_Shell/blob/9e532c6a52e195d55d067411fdec83055ecee1e7/myshell.c) file and give a name for the output file**

```
gcc shell.c -lreadline -o myshell
```

**5. Run it**

```
./myshell
```

**6. Run from anywhere by setting the $PATH variable**

```
echo 'export PATH=$PATH:/path_to_directory/where_myshell_exists' >> ~/.bash_profile
```
```
echo 'export PATH=$PATH:/path_to_directory/where_myshell_exists' >> ~/.bashrc
```
 **Close and reopen terminal.**
 **Now you should be able to run myshell command from anywhere**
```
myshell
```

### 💻Executing in macOS (Unix based system)

**Since macOS has libedit by default, that has the libreadline library, we don't really have to install the GNU readline library atleast in this case.**

**1. Download the [myshell.c](https://github.com/hy-atharv/My_Shell/blob/9e532c6a52e195d55d067411fdec83055ecee1e7/myshell.c)**

**2. Navigate to the directory where you downloaded [myshell.c](https://github.com/hy-atharv/My_Shell/blob/9e532c6a52e195d55d067411fdec83055ecee1e7/myshell.c)**

**3. Link the readline and compile the [myshell.c](https://github.com/hy-atharv/My_Shell/blob/9e532c6a52e195d55d067411fdec83055ecee1e7/myshell.c) file and give a name for the output file**

```
gcc shell.c -lreadline -o myshell
```

**4. Run it**

```
./myshell
```

**5. Run from anywhere by setting the $PATH variable**

```
echo 'export PATH="/path_to_directory/where_myshell_exists:$PATH"' >> ~/.zshrc
```
```
echo 'export PATH="/path_to_directory/where_myshell_exists:$PATH"' >> ~/.bash_profile
```
 **Close and reopen terminal.**
 **Now you should be able to run myshell command from anywhere**
```
myshell
```


### 🔨Under Development (might work on it in near future)
- **Terminal based game**
- **Cybersecurity toolkit**

