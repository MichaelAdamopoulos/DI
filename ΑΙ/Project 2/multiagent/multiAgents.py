# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent
from pacman import GameState

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState: GameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState: GameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        score = 0.0

        # The closer the food, the better
        for food in newFood.asList():
            if  manhattanDistance(newPos, food) <= 2:
                score += 2
            elif 2 < manhattanDistance(newPos, food) <= 4:
                score += 1
            elif 4 < manhattanDistance(newPos, food) <= 8:
                score += 0.5
            elif 8 < manhattanDistance(newPos, food) <= 16:
                score += 0.2
            else:
                score += 0.1
        
        # The closer the ghost, the worse
        for ghost in successorGameState.getGhostPositions():
            # GHOST IS TOO CLOSE!
            if manhattanDistance(ghost, newPos) <= 2.5:
                score = float('-inf')
            elif 2.5 < manhattanDistance(ghost, newPos) <= 5:
                score -= 5
            elif 5 < manhattanDistance(ghost, newPos) <= 10:
                score -= 2.5

        return successorGameState.getScore() + score

def scoreEvaluationFunction(currentGameState: GameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        
        # Minimax returns a tuple of (value, action) so we can keep track of the actions
        def minimax(gameState, depth, agentIndex):
            Actions = gameState.getLegalActions(agentIndex)
            # If terminal state
            if depth == self.depth or gameState.isWin() or gameState.isLose() or not Actions:
                return (self.evaluationFunction(gameState), None)
            
            # Pacman plays 
            if (not agentIndex):
                max_value = float('-inf')
                action = None
                for a in Actions:
                    result = minimax(gameState.generateSuccessor(agentIndex, a), depth, agentIndex + 1)
                    if result[0] > max_value:
                        max_value = result[0]
                        action = a
                return (max_value, action)
            
            else:
                min_value = float('+inf')
                action = None
                for a in Actions:
                    # If last ghost plays --> pacman plays for new depth
                    if (agentIndex == gameState.getNumAgents() - 1):
                        result = minimax(gameState.generateSuccessor(agentIndex, a), depth + 1, 0)
                        if result[0] < min_value:
                            min_value = result[0]
                            action = a
                    # If there are more ghosts to play --> next ghost plays
                    else:
                        result = minimax(gameState.generateSuccessor(agentIndex, a), depth, agentIndex + 1)
                        if result[0] < min_value:
                            min_value = result[0]
                            action = a
                return (min_value, action)
        
        return minimax(gameState, 0, 0)[1]
        util.raiseNotDefined()

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        # AlphaBetaAgent is the same as MinimaxAgent, except we add one
        # inequality check for alpha and beta.
        
        # Alphabeta returns a tuple of (value, action) so we can keep track of the actions
        def alphabeta(gameState, depth, agentIndex, alpha, beta):
            Actions = gameState.getLegalActions(agentIndex)
            # If terminal state
            if depth == self.depth or gameState.isWin() or gameState.isLose() or not Actions:
                return (self.evaluationFunction(gameState), None)
            
            # Pacman plays 
            if (not agentIndex):
                max_value = float('-inf')
                action = None
                for a in Actions:
                    result = alphabeta(gameState.generateSuccessor(agentIndex, a), depth, agentIndex + 1, alpha, beta)
                    if result[0] > max_value:
                        max_value = result[0]
                        action = a
                    if result[0] > beta:
                        return (max_value, action)
                    alpha = max(alpha, result[0])
                return (max_value, action)
            
            else:
                min_value = float('+inf')
                action = None
                for a in Actions:
                    # If last ghost plays --> pacman plays for new depth
                    if (agentIndex == gameState.getNumAgents() - 1):
                        result = alphabeta(gameState.generateSuccessor(agentIndex, a), depth + 1, 0, alpha, beta)
                        if result[0] < min_value:
                            min_value = result[0]
                            action = a
                        if result[0] < alpha:
                            return (min_value, action)
                        beta = min(beta, result[0])
                    # If there are more ghosts to play --> next ghost plays
                    else:
                        result = alphabeta(gameState.generateSuccessor(agentIndex, a), depth, agentIndex + 1, alpha, beta)
                        if result[0] < min_value:
                            min_value = result[0]
                            action = a
                        if result[0] < alpha:
                            return (min_value, action)
                        beta = min(beta, result[0])
                return (min_value, action)
        
        return alphabeta(gameState, 0, 0, float('-inf'), float('+inf'))[1]
        
        util.raiseNotDefined()

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        
        # ExpectimaxAgent is the same as MinimaxAgent, except min_value is
        # calculated as a average of all the possible values
        
        # Expectimax returns a tuple of (value, action) so we can keep track of the actions
        def expectimax(gameState, depth, agentIndex):
            Actions = gameState.getLegalActions(agentIndex)
            # If terminal state
            if depth == self.depth or gameState.isWin() or gameState.isLose() or not Actions:
                return (self.evaluationFunction(gameState), None)
            
            # Pacman plays 
            if (not agentIndex):
                max_value = float('-inf')
                action = None
                for a in Actions:
                    result = expectimax(gameState.generateSuccessor(agentIndex, a), depth, agentIndex + 1)
                    if result[0] > max_value:
                        max_value = result[0]
                        action = a
                return (max_value, action)
            
            else:
                min_value = 0
                action = None
                for a in Actions:
                    # If last ghost plays --> pacman plays for new depth
                    if (agentIndex == gameState.getNumAgents() - 1):
                        min_value += expectimax(gameState.generateSuccessor(agentIndex, a), depth + 1, 0)[0]
                        action = a
                    # If there are more ghosts to play --> next ghost plays
                    else:
                        min_value += expectimax(gameState.generateSuccessor(agentIndex, a), depth, agentIndex + 1)[0]
                        action = a
                return (min_value / len(Actions), action)
        
        return expectimax(gameState, 0, 0)[1]
        util.raiseNotDefined()

def betterEvaluationFunction(currentGameState: GameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    score = 0.0

    # Terminal states
    if currentGameState.isLose():
        score = float('-inf')
        
    if currentGameState.isWin():
        score = float('+inf')
        
    # Each food awards 10 points, so extract 10 points for every food not eaten
    # Also, the furthest the food, the worse
    for food in currentGameState.getFood().asList():
        score -= 10 + manhattanDistance(food, currentGameState.getPacmanPosition())

    # Same for capsules, but for 50 points because they are more important
    # We do not care about distance, because we do not want pacman to
    # actively chase capsules
    for capsule in currentGameState.getCapsules():
        score -= 50
    
    # The closer a feared ghost the better, the closer a fearless the worse
    for ghost in currentGameState.getGhostStates():
        if ghost.scaredTimer:
            score += manhattanDistance(currentGameState.getPacmanPosition(), ghost.getPosition())
        else:
            score -=  manhattanDistance(currentGameState.getPacmanPosition(), ghost.getPosition())      

    return currentGameState.getScore() + score
    
    util.raiseNotDefined()

# Abbreviation
better = betterEvaluationFunction
