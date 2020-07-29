# Watopoly
## Game Description
A board game based on Monopoly.

A game of Watopoly consists of a board that has 40 squares. When a player moves, an action specific to the square they land on occurs. The goal of the game is to be the only player to not drop out of university (declare bankruptcy). Play proceeds as follows: players take turns moving around the board, buying and improving on-campus buildings (properties), and paying tuition (rent).

### Definitions
- **Board** The board is the visual representation of the state of the current game. The board should always display the 40 squares, any improvements for an academic building, and a representation for each player in the game which shows their current location on the board. There are two types of squares on the board: ownable properties (academic buildings, gyms, and residences) and unownable buildings (e.g. run by administration).
- **Buildings** The squares on the board represent buildings or locations on campus. Different buildings have different purposes. Academic buildings can be purchased by players, which allows tuition to be charged to other players for attending lectures in said building. Each Academic Building is part of a smaller collection of properties, known as a monopoly. When a player owns multiple buildings from a monopoly, the calculation of tuition changes depending on the type of property 1 . If a player lands on an unowned Academic building, they may choose to purchase the property for its corresponding value. A player may choose not to purchase a property. If this happens the bank will auction the property (see the Auctions section). If the property is owned by another player, the player must pay the appropriate tuition to the owner.
- **Players** All players in the game will be “human” players and controlled by the commands described in the Command Interpreter section and any other commands you implement and document. Your game must support at least 6 players. Note that the given display (which you do not need to follow precisely) cannot support the full 8 players that Monopoly supports because of the number of tiles used for each building.

A player chooses from the following pieces to represent them on the board. Only one player may choose a particular piece.

| Name | Goose | GRT Bus | Tim Hortons Doughnut | Professor | Student | Money | Laptop | Pink tie |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| Char | G | B | D | P | S | $ | L | T |

## Command Interpreter
- roll (used if the player can roll): the player rolls two dice, moves the sum of the two dice and takes action on the square they landed on.
- next (used if the player cannot roll): give control to the next player.
- trade &lt;name&gt; &lt;give&gt; &lt;receive&gt;: offers a trade to name with the current player offering give and requesting receive, where give and receive are either amounts of money or a property name. Responses are accept and reject. For example,
- trade Brad 500 DC indicates that the current player is willing to give Brad $500 in exchange for the DC building
- trade Rob DC MC indicates that the current player is willing to give Rob DC in exchange for MC
- trade Kevin MC 500 indicates that the current player is willing to give Kevin MC in exchange for $500
- improve &lt;property&gt; buy/sell: attempts to buy or sell an improvement for property.
- mortgage &lt;property&gt;: attempts to mortgage property.
- unmortgage &lt;property&gt;: attempts to unmortgage property.
- bankrupt: player declares bankruptcy. This command is only available when a player must pay more money then they currently have.
- assets: displays the assets of the current player. Does not work if the player is deciding how to pay Tuition.
- all: displays the assets of every player. For verifying the correctness of your transactions. Does not work if a player is deciding how to pay Tuition.
- save &lt;filename&gt;: saves the current state of the game (as per the description below) to the given file.
## Gameplay
A typical turn should be played as follows:

When not in the middle of another action, the player can offer a trade, buy/sell improvements, and mortgage/unmortgage buildings they own. 

If the player is in the DC Tims Line, they follow the procedure to leave.

Otherwise, the player rolls two six-sided dice. Their token moves the sum of dice. They take the action of the square they landed on. If they rolled doubles, they roll again. If they roll three sets of doubles in a row, they do not move the number shown on the last set and move to DC Tims Line 3 instead and cannot
roll again.

When the player cannot roll, they can finish their turn.

At any time when a player must pay more money than they currently have, they have the option to drop out (declare bankruptcy) or attempt to trade, mortgage buildings and sell improvements to gather the required money.
## assets
    ...
## Command Line Options
    ...
## Installings
    ...
## Authors
    ...
## References
    ...

