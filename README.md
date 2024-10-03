This project was done by:

Leila Dantas - https://github.com/leilatdantas

Uatilla  Almeida - https://github.com/Uatilla

# Minishell
![Screencastfrom2024-10-0211-42-55-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/4b41ef52-b0bd-4490-b691-3bc39729518d)

**Minishell** is a C project developed as part of the 42 School Common Core Program. It is a smaller shell environment that adheres to POSIX standards and aims to replicate some of the behavior of the original Unix shell program. The primary objectives of this project are to:
 
    *Handling environment variables
    *Managing variable expansions
    *Executing commands
    *Managing redirections, including heredoc, append, input files, and output files
    *Managing pipes and command chaining
    *Error handling and reporting
    *Basic signal handling in child and/or parent processes
    *Handling other basic shell features

    

Understanding the construction of **Abstract Syntax Trees (ASTs)** [see more](https://en.wikipedia.org/wiki/Abstract_syntax_tree), was one of the most fascinating aspects of this project. This task was also one of the most challenging and rewarding parts of the project, as it required a deep understanding of C programming concepts and data structures.

For more detailed information, look at the [**subject of this project**](https://cdn.intra.42.fr/pdf/pdf/138331/en.subject.pdf).

## How to use it

### Getting Started
**Program overview:**
![image](https://github.com/user-attachments/assets/360bf9e6-a80e-4f8e-9587-71d3cc9b266c)


## Usage

If you want to run the project yourself:

	- First clone this git repository to your machine.
 
	- Enter the repo and run ``` make ```
 
	- The first time will download and set up the minilibx
 
	- Run ./minishell

## Rules

**Norminette:**

The Norminette is a tool provided by 42 Network to check whether the source code complies with the school's norm. The rules include the prohibition of ‘for’ loops, a limit of 25 lines, and no more than 4 parameters in each function, among other specifications.

Here is a [link](https://github.com/gdamion/Norminette/blob/master/norme.en.pdf) to more details about what is evaluated by the Norminette tool.


# Technical overview

## Syntax Analysis

![screencast-from-2024-10-03-13-24-13_ss5HZxb8-ezgif com-resize](https://github.com/user-attachments/assets/d7bbc5b2-26ca-4acd-8db3-b966d8b271e9)

The syntax analysis is a very good approach to take in this project, since there are many details to handle and Minishell represents a significant increase in complexity compared to previous projects in the Common Core. This helps improve the quality of the input and ensures that only valid commands will be processed by your project.
- Examples of syntax errors:
>

	command1 > | command2
 	command1 >>> command2
	command1 | | command2 	
 


- Once the input has been validated it's time to go ahead and tokenize it.
![image](https://github.com/user-attachments/assets/144f8e76-d0cb-4127-83e7-b2aedb15a6aa)


## Lexer
![image](https://github.com/user-attachments/assets/d5efc80e-00eb-447a-a5e6-3b06d454b60d)


The Lexer is where the input will be transformed into something more suitable for the program to use. The result of this step is called **tokens**. 
Tokens are the smallest "unit" of the command that the program can handle accordingly. For this reason, the tokenization will consider aspects of the input, such as *what is the type of this command?*, *is it in quotes?*, *is it in double or single quotes?*, or *should this command be expanded?*. Having the answers to these questions will help ensure the correct processing, construction, and execution of the binary tree.

### Token Structures
See here which kind of information each node of the token list has:

```c
typedef struct s_token
{
	char		*value;
	t_token_type	type;
	t_token_state	state;
	int		pos;
	bool		not_expand;
}	t_token;
```

```c
typedef enum s_token_type
{
	WORD,
	PIPE,
	GREATER,
	LESSER,
	D_GREATER,
	D_LESSER,
	E_SPACE,
	APPEND,
	OUTFILE,
	INFILE,
	HEREDOC
}	t_token_type;
```

```c
typedef enum s_token_state
{
	GENERAL,
	IN_DQUOTES,
	IN_SQUOTES
}	t_token_state;
```
### Explaining in details
#### Quotes
![image](https://github.com/user-attachments/assets/889f83bb-2676-436c-9aab-d0efc8c8b77b)

For more details about quoting in bash [see the manual](https://www.gnu.org/software/bash/manual/bash.html#Quoting).

#### Token Nodes
![image](https://github.com/user-attachments/assets/1ef8baee-0abe-4538-9341-62576bfff01a)

For more details about how the redirection works in bash [see the manual](https://www.gnu.org/software/bash/manual/bash.html#Redirections).

### Token List
After applying the logic previously explained here is the token list result of our input:
  
![image](https://github.com/user-attachments/assets/ebefa809-fee1-45e1-9d68-16e337791cc1)


## Parsing the Abstract Syntax Tree - AST

![image](https://github.com/user-attachments/assets/f54d8149-0cf9-40b4-8d0b-a80fff469ff5)

## Executing


# Credits

This project would not be possible without the guidelines of the video:

**Shell Program Explained and Shell Code-- More Detail**
Both videos from HHP3 on YouTube, it's just the best content!
 I strongly recommend to anyone who wants to build this project from scratch, that deep dive on these videos, there is a lot of valuable information there [here](https://www.youtube.com/watch?v=ubt-UjcQUYg) and [here](https://www.youtube.com/watch?v=ZjzMdsTWF0U).

Don't forget to go directly to the source: **RTFM** [Link](https://www.gnu.org/software/bash/manual/bash.html#Introduction)
## Contributing

Contributions to the project are welcome! If you have any ideas, improvements, or bug fixes, please submit them as issues or pull requests to this repository.

<div align="center">
  <h1><b>Welcome to my new brave world!</b></h1> 
  <h2><b>00100010 01000010 01100101 00100000 01110111 01100001 01110100 01100101 01110010 00100000 01101101 01111001 00100000 01100110 01110010 01101001 01100101 01101110 01100100 00100010 00100000 01000010 01110010 01110101 01100011 01100101 00100000 01001100 01100101 01100101</b></h2>
</div>

<!---
SMALL ICONS
--->
<div style="text-align: center;">
  <a href='https://www.linkedin.com/in/uatilla' target="_blank" style="display: inline-block; margin: 0 10px;">
    <img alt='Linkedin' src='https://img.shields.io/badge/LinkedIn-100000?style=flat&logo=Linkedin&logoColor=white&labelColor=0A66C2&color=0A66C2'/>
  </a>
  <a href='https://profile.intra.42.fr/users/uviana-a' target="_blank" style="display: inline-block; margin: 0 10px;">
    <img alt='42' src='https://img.shields.io/badge/Porto-100000?style=flat&logo=42&logoColor=white&labelColor=000000&color=000000'/>
  </a>
  <img src="https://komarev.com/ghpvc/?username=uatilla&label=Profile%20views&color=0e75b6&style=flat" alt="uatilla" style="display: inline-block; margin: 0 10px;" />
</div>


## About me

- 👋 I'm `Uatilla Viana Almeida`.
- 🌱 I'm currently studying Common Core at [**42 Porto**](https://www.42porto.com) after successfully completing the Piscine.
- 👀 I'm interested in `Bitcoin`, `Games` and `Sports` of all kinds.
- 🚀 Additionally, I have an interest in `AI`, `Python`, `Data Analysis` and `Project Management`.
- 📫 You can reach me on [**LinkedIn**](https://www.linkedin.com/in/uatilla/).
- 🤔 Feeling amazing about how AI can help our society.

<div align="center">

## Skills
<p align="left">
  <a href="https://skillicons.dev">
    <img src="https://skillicons.dev/icons?i=c,python,git,github,bash,linux,vim,vscode,sketchup,sql" />
  </a>
</p>

<p><img align="left" src="https://github-readme-stats.vercel.app/api/top-langs?username=uatilla&show_icons=true&locale=en&layout=compact" alt="uatilla" /></p>

<p>&nbsp;<img align="left" src="https://github-readme-stats.vercel.app/api?username=uatilla&show_icons=true&locale=en" alt="uatilla" /></p>

<p><img align="left" src="https://github-readme-streak-stats.herokuapp.com/?user=uatilla&" alt="uatilla" /></p>
