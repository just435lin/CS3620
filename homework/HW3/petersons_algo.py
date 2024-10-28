from graphviz import Digraph
import queue

class State:
    StateCnt = 0
    def __init__(self):
        State.StateCnt += 1
        self.ID = self.StateCnt
        self.turn : int = 0
        self.try0 : bool = False
        self.try1 : bool = False
        self.pc0 : int = -1
        self.pc1 : int = -1

        self.children = []

    def add_child(self, child):
        self.children.append(child)

    def copy(self):
        copy_state = State()
        copy_state.turn = self.turn
        copy_state.try0 = self.try0
        copy_state.try1 = self.try1
        copy_state.pc0 = self.pc0
        copy_state.pc1 = self.pc1
        return copy_state

    def label(self):
        label = f'<<TABLE BORDER="0"><TR><TD PORT="f0">turn:{self.turn}</TD></TR><TR><TD PORT="f1">try0:{self.try0}</TD></TR><TR><TD PORT="f2">try1:{self.try1}</TD></TR><TR><TD PORT="f3">pc0:{self.pc0}</TD></TR><TR><TD PORT="f4">pc1:{self.pc1}</TD></TR></TABLE>>'
        return label

def render(all_states):
    dot = Digraph(format='pdf')
    for state in all_states:
        dot.node(str(encodeState(state)), label=state.label(), shape='record') 

        for child in state.children:
            dot.edge(str(encodeState(state)), str(encodeState(child)))
    dot.render("state_graph", cleanup=True)
    dot.view()


def compute_next_state(state : State, proc : int):
    next_state = state.copy()
    if proc == 0:
        match next_state.pc0:
            case -1:
                pass
            case 0:
                next_state.try0 = True
            case 1:
                next_state.turn = 1
            case 2:
                if (next_state.try1 and next_state.turn != 0):
                    next_state.pc0 -= 1
            case 3:
                pass
            case 4:
                next_state.try0 = False
            case 5:
                next_state.pc0 = -1
        next_state.pc0 += 1
    else:
        match next_state.pc1:
            case -1:
                pass
            case 0:
                next_state.try1 = True
            case 1:
                next_state.turn = 0
            case 2:
                if (next_state.try0 and next_state.turn != 1): #stays in same state
                    next_state.pc1 -= 1
            case 3:
                pass
            case 4:
                next_state.try1 = False
            case 5:
                next_state.pc1 = -1
        next_state.pc1 += 1

    return next_state

def explore_all_states():
    visitedDict = {}        #dictionary of encoded states which points to a visited state, easy way of checking duplicates
    allStates = []          #list of states that we will pass to renderer
    stateQ = queue.Queue()
    init_state = State()
    stateQ.put(init_state)

    while not stateQ.empty():
        curr = stateQ.get()
        encodedState = encodeState(curr)
        if encodedState not in visitedDict:
            visitedDict[encodedState] = curr
            allStates.append(curr)
            proc0_State = compute_next_state(curr,0)
            if encodeState(proc0_State) in visitedDict:
                curr.add_child(visitedDict[encodeState(proc0_State)])
            else:
                curr.add_child(proc0_State)
                stateQ.put(proc0_State)
            proc1_State = compute_next_state(curr,1)
            if encodeState(proc1_State) in visitedDict:
                curr.add_child(visitedDict[encodeState(proc1_State)])
            else:
                curr.add_child(proc1_State)
                stateQ.put(proc1_State)
    
    return allStates
    
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
    