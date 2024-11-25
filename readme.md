```
 _____                                                                    _____ 
( ___ )                                                                  ( ___ )
 |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   | 
 |   |                                                                    |   | 
 |   |   ██████╗  ██████╗ ███████╗███████╗██╗██████╗  ██████╗ ████████╗   |   | 
 |   |   ██╔══██╗██╔═══██╗██╔════╝██╔════╝██║██╔══██╗██╔═══██╗╚══██╔══╝   |   | 
 |   |   ██████╔╝██║   ██║███████╗█████╗  ██║██████╔╝██║   ██║   ██║      |   | 
 |   |   ██╔═══╝ ██║   ██║╚════██║██╔══╝  ██║██╔══██╗██║   ██║   ██║      |   | 
 |   |   ██║     ╚██████╔╝███████║███████╗██║██████╔╝╚██████╔╝   ██║      |   | 
 |   |   ╚═╝      ╚═════╝ ╚══════╝╚══════╝╚═╝╚═════╝  ╚═════╝    ╚═╝      |   | 
 |   |                                                                    |   | 
 |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___| 
(_____)                                                                  (_____)
```

# PoseiBot - Battleship AI

PoseiBot is an AI-driven opponent for the classic game of Battleship. This project was a way to start with some serius (ish) C++ programming, combaining this with the implemetation of greedy strategie (another thing i had never used before in a project).
## Table of Contents
[Description](#description)
[Features](#features)
[Inspiration](#inspiration)
[Installation](#installation)
[Usage](#usage)
[Contributing](#contributing)
[License](#license)

## Description

PoseiBot offers an intelligent opponent for Battleship, designed for players who want to test their strategic skills. The bot adapts its ship placement and attack strategies based on various heuristics to make gameplay engaging.

This project was built to explore game AI development and improve understanding of decision-making algorithms in games. It uses modular design principles, making it a foundation for future improvements and expansions.

## Motivation
To challenge myself in AI and game development.
To provide a platform for learning and experimenting with decision-making algorithms.

### Technologies Used
C++: Primary programming language for its performance and modularity (also i used this project as an excuse for learning the project).

## Features
Intelligent Ship Placement: Weighted placement to avoid predictable patterns.
Adaptive Attack Strategy: Analyzes hits and misses to refine targeting.
Modular Design: Easily extendable for future enhancements or custom rules.
    
## Inspiration
I was inspired from a series of people to make a project about an IA oponent in a game such as [Primer](https://www.youtube.com/@PrimerBlobs) and [Code Bullet](https://www.youtube.com/@CodeBullet). My profesors at IPS introduced me to greedy strategies and I wanted test it and a series of papers where i found what general strategies to implement:
1. Audinot, M., Bonnet, F., & Viennot, S. (2014, October). Optimal strategies against a random opponent in battleship. In The 19th Game Programming Workshop.
2. Sakuta, M., & Iida, H. (2003). Evaluation of Attacking and Placing Strategies in the Battleship Game without Considering Opponent Models. In Proceedings of 1st International Forum on Information and Computer Technology, Shizuoka University, Hamamatsu, Japan, 2003.
3. [Coding an Intelligent Battleship Agent](https://towardsdatascience.com/coding-an-intelligent-battleship-agent-bf0064a4b319)

## Installation
Clone this repository:

`git clone https://github.com/ignacio-joaquin/PoseiBot.git`

Navigate to the project directory:

`cd poseibot  `

Build the project:

`make  `

Run the game:
`./poseibot  `

## Usage
Upon launching, follow the on-screen instructions to place your ships.
Play against PoseiBot and see how its AI adapts to your moves!


## Contributing

Contributions are welcome!
Fork the repository.
Create a new branch:

`git checkout -b feature-name  `

Make your changes and commit them:

`git commit -m "Add some feature"  `

Push to the branch:
`git push origin feature-name  `
Open a pull request.

## License

This work is licensed under a
[Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](license).