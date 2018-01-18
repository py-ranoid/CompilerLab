#Do two things
#decide when to turn and where to turn

import gym
import universe
import random

#Reinforcement  learning step 
def determine_turn(turn , observation_n , j , total_sum , prev_total_sum , reward_n):
    #for every 15+ iterations , sum the total obs , and take average
    #if its lower than 0 , change the direction
    #if we go 15+ iteration and get reward each step , we are doing something right
    #and thats when we turn
    if( j >= 5):

        if(total_sum/j) == 0:
            turn = True
        else:
            turn = False

        #now going to reset these variables
        prev_total_sum = total_sum
        total_sum = 0
        j = 0

    else:
        turn = False

    if(observation_n != None): #if we have some observation
        #we increment the counter , reward sum
        j += 1
        total_sum += reward_n

    return (turn , j , total_sum , prev_total_sum)


def main():

    #initialize our environment
    env = gym.make('flashgames.CoasterRacer-v0') #to define the env

    #VNC helps you see what happens in another computer
    #Since we wiill be using docker containers

    #client is the agent and the remote is the environment(local)
    #The env.conf command helps the local host attach it to the VNC server automaticaaly
    
    env.configure(remotes=1)    
    observation_n = env.reset() #initialize our environment

    #Initialize our variables

    #Number of game iterations
    n = 0
    j = 0

    #Sum of observations
    total_sum = 0
    prev_total_sum = 0
    turn = False #based on whether its true or false , we will turn

    #Define our keyboard actions
    left = [('KeyEvent' , 'ArrowUp' , True) , ('KeyEvent' , 'ArrowLeft' , True) , ('KeyEvent' , 'ArrowRight' , False)]
    right = [('KeyEvent' , 'ArrowUp' , True) , ('KeyEvent' , 'ArrowRight' , True) , ('KeyEvent' , 'ArrowLeft' , False)]
    forward = [('KeyEvent' , 'ArrowUp' , True) , ('KeyEvent' , 'ArrowRight' , False) , ('KeyEvent' , 'ArrowLeft' , False)]

    #pixel data is returned via the observation variable

    #main logic

    while True:
        #increment a counter for number of iterations
        n += 1

        #if atleast one iteration is made , check if turn is needed
        if (n > 1):
            #if atleast one iteration , check if a turn is required
            if (observation_n[0] != None): #we only have one game , so that one games value is in obs[0]
                #Store the reward in the previous score
                prev_score = reward_n[0]



                if(turn):
                    #pick a random event
                    event = random.choice([left , right]) # which direction to turn
                    #Perform an action
                    action_n = [event for ob in observation_n] 
                    #Set turn to false again
                    turn = False
                
                elif(~turn):
                    #If no turn is needed , go straight
                    action_n = [forward for ob in observation_n]

            #if there is an observation, game has started , check if turn is needed

            if (observation_n[0] != None):
                turn , j , total_sum , prev_total_sum = determine_turn(turn , observation_n[0] , j , total_sum , prev_total_sum , reward_n[0])

            #save new variables for each iteration 

        observation_n , reward_n , done_n , info = env.step(action_n)

        env.render()

if __name__ == '__main__':
    main()