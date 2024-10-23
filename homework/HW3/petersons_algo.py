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
        #label = "<record><f0>Record {self.ID} | </f0><f1>Details about A</f1>|<f2>More info here</f2></record>"
        #label = f'<record><f0>{self.ID} | </f0><f1>{self.try0}</f1>|<f2>{self.try1}</f2></record>'


        #Below is what I want, I followed the format GPT gave me doesn´t work, gives a error near 'turn' message
        label = f'<record><turn>turn: {self.turn}| <turn><try0>try0: {self.try0}<try0>| <try1>try1: {self.try1}<try1>| <pc0>pc0: {self.pc0}<pc0>| <pc1>pc1: {self.pc1}<pc1></record>'
        
        #label = '<record>test<record>'  #This short thing also doesn´t work gives a error near '>' message
        return label

def render(all_states):
    dot = Digraph(format='pdf')
    for state in all_states:
        dot.node(str(encodeState(state)), label=state.label(), shape='record') #This is what I want to do but my label is incorrect

        #dot.node(str(encodeState(state)), str(encodeState(state)),shape='record')  #This currently just names each node 
                                                                                #as its state in the format of an int casted to string
                                                                                #so leading zeroes are left off, just temporary solution so I can see my states are correct
        
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
    print(len(all_states))
    render(all_states)
    
    if False:
        # Create a new directed graph
        dot = Digraph(comment='Graph with Record Labels', format='pdf')

        # Define nodes using the <record> structure
        dot.node('A', label='<record><f0>Record A | </f0><f1>Details about A</f1>|<f2>More info here</f2></record>')
        dot.node('B', label='<record><f0>Record B | </f0><f1>Details about B</f1>|<f2>More info here</f2></record>')
        dot.node('C', label='<record><f0>Record C | </f0><f1>Details about C</f1>|<f2>More info here</f2></record>')
        dot.node('D', label='<record><f0>Record D | </f0><f1>Details about D</f1>|<f2>More info here</f2></record>')

        # Add edges (relationships between records)
        dot.edge('A', 'B', label='related to')
        dot.edge('A', 'C', label='refers to')
        dot.edge('B', 'D', label='points to')
        dot.edge('C', 'D', label='connects to')

        # Render the graph to a file and display it
        dot.render('records_with_record_labels', cleanup=True)

        # If you want to visualize it directly
        dot.view()
