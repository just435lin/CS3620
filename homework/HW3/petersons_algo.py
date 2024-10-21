from graphviz import Digraph
import queue

class State:
    StateCnt = 0
    def __init__(self):
        State.StateCnt += 1
        self.turn : int = 0
        self.try0 : bool = False
        self.try1 : bool = False
        self.pc0 : int = -1
        self.pc1 : int = -1

        self.children = []

    def add_child(child):
        self.children.append(child)

    def copy(self):
        copy_state = State()
        copy_state.turn = self.turn
        copy_state.try0 = self.try0
        copy_state.try1 = self.try1
        copy_state.pc0 = self.pc0
        copy_state.pc1 = self.pc1
        

    def label():
        label = f'{{State {self.StateCnt}|turn: {self.turn}|try0: {self.try0}|try1: {self.try1}|pc0: {self.pc0}|pc1: {self.pc1}}}'
        return label

def render(all_states):

    dot = Digraph()


def compute_next_state(state : State, proc : int):
    next_state = state.copy()
    if proc == 0:
        if state.pc0 == -1:
            next_state.try0 = True

    return next_state

def explore_all_states():
    statesVisited = {}  #set of encoded states, easy way of checking duplicates
    allStates = []      #list of states that we will pass to renderer
    stateQ = queue.Queue()
    init_state = State()
    stateQ.put(init_state)

    while not stateQ.empty():
        curr = stateQ.get()
        encodedState = encodeState(curr)
        if encodedState not in statesVisited:
            statesVisited.add(encodedState)
            allStates.add(curr)
            stateQ.put(compute_next_state(curr,0))
            stateQ.put(compute_next_state(curr,1))
        
    
def stateEqual(s1 : State, s2 : State):
    equal = False
    if (encodeState(s1) == encodeState(s2)):
        equal = True
    return equal

def encodeState(state : State):
    code = 0
    #encode the State
    if (state.pc0 == -1):
        code += 90
    else:
        code += state.pc0*10
    if (state.pc1 == -1):
        code += 9
    else:
        code += state.pc1
    code += state.turn*10000 + state.try0*1000 + state.try1*100
    return code                 #each decimal space is a piece of information from the state

if __name__ == '__main__':
    all_states = explore_all_states()
    render(all_states)