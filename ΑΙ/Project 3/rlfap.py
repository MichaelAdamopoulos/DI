from csp import CSP, forward_checking, lcv, mac, backtracking_search, min_conflicts, mrv
import random
from math  import inf
import time

def solve(file):
    # Reading data
    fvar = open("rlfap/var" + file + ".txt")
    fdom = open("rlfap/dom" + file + ".txt")
    fctr = open("rlfap/ctr" + file + ".txt")

    variables = []
    domains = {}
    neighbors = {}

    fvar.readline()
    for varline in fvar:
        varline = varline.split()
        variables.append(int(varline[0]))
        fdom.seek(0)
        for _ in range(int(varline[1]) + 1):
            fdom.readline()
        domline = fdom.readline().split()[2:]
        domainlist = [int(x) for x in domline]
        domains[int(varline[0])] = domainlist

    fctr.readline()
    for line in fctr:
        parts = line.split()
        var_a = int(parts[0])
        var_b = int(parts[1])
        if var_a in neighbors:
            neighbors[var_a].append(var_b)
        else:
            neighbors[var_a] = [var_b]
        if var_b in neighbors:
            neighbors[var_b].append(var_a)
        else:
            neighbors[var_b] = [var_a]
            
    fctr.seek(0)
    fctr.readline()
    constraints_dict = {} # Dictionary for constrains

    for line in fctr:
        parts = line.split()
        var1, var2 = map(int, parts[0:2])
        operator = parts[2]
        value = int(parts[3])

        constraints_dict[(var1, var2)] = (operator, value)
        constraints_dict[(var2, var1)] = (operator, value)

    def constraints(A, a, B, b):
        operator, value = constraints_dict[(A,B)]
        if operator == '=':
            return abs(a-b) == value
        elif operator == '>':
            return abs(a-b) > value
    
    # Function to initialize variables for DOM-WDEG
    def csp_init_dom_wdeg(csp):
        csp.weights = {}
        for var in csp.neighbors:
            for neighbor in csp.neighbors[var]:
                csp.weights[(var, neighbor)] = 1
                
    # DOM_WDEG Heuristic
    def dom_wdeg(assignment, csp):
        
        min_ratio, target = inf, None
        for var in csp.variables:
            if var not in assignment:
                not_assigned_neighbors = []
                for neighbor in csp.neighbors[var]:
                    if neighbor not in assignment:
                        not_assigned_neighbors.append(neighbor)
                weight = 0
                for not_assigned_neighbor in not_assigned_neighbors:
                    weight += csp.weights[(var, not_assigned_neighbor)]
                if weight:
                    ratio = len(csp.choices(var)) / weight
                else:
                    ratio = len(csp.choices(var))
                if min_ratio > ratio:
                    target = var
                    min_ratio = ratio
        return target
       
    # FC-CBJ
    def fc_cbj(csp, select_unassigned_variable, order_domain_values, inference):

        def backjump(assignment):   # Returns (assignment, jump_variable)
            if len(assignment) == len(csp.variables):
                return assignment, None
            if time.time() - csp.start > 500: # Timeout
                return -1, None
            var = select_unassigned_variable(assignment, csp)
            for value in order_domain_values(var, assignment, csp):
                if 0 == csp.nconflicts(var, value, assignment):
                    csp.assign(var, value, assignment)
                    removals = csp.suppose(var, value)
                    if inference(csp, var, value, assignment, removals):
                        result, jump_var = backjump(assignment)
                        if result is not None:  # Result found
                            return result, None
                        elif var in csp.visited and var != jump_var: # We need to check that var is not the jump_variable
                            csp.conf_set[var].clear()
                            csp.visited.discard(var)
                            csp.restore(removals)
                            csp.unassign(var, assignment)
                            return None, jump_var 
                    for domain_wipeout_var in csp.domains:  # Find domain_wipeout_var 
                        if not csp.domains[domain_wipeout_var]:
                            csp.conf_set[domain_wipeout_var].add(var)
                    csp.restore(removals)
            csp.unassign(var, assignment)
            csp.visited.add(var)
            jump_var = None
            if len(csp.conf_set[var]):  # Find jump_variable
                jump_var = list(csp.conf_set[var])[-1]
                csp.conf_set[jump_var].union(csp.conf_set[var])
                csp.conf_set[jump_var].discard(jump_var)             
            return None, jump_var
        
        csp.conf_set = {var: set() for var in variables} # Dictionary of var : conflict sets
        csp.visited = set()
        csp.start = time.time()
        csp.assignments = 0
        
        result = backjump({})
        if result[0] == -1:
            print("Timeout")
            return None
        assert result[0] is None or csp.goal_test(result[0])
        print("Time = ", time.time() - csp.start)
        return result[0]

    # Running csp and printing results
    print(file, ":")

    FC = CSP(variables, domains, neighbors, constraints)
    csp_init_dom_wdeg(FC)
    print("FC:")
    backtracking_search(FC, dom_wdeg, lcv, forward_checking)
    print("Assignments = ", FC.nassigns)

    MAC = CSP(variables, domains, neighbors, constraints)
    csp_init_dom_wdeg(MAC)
    print("MAC:")
    backtracking_search(MAC, dom_wdeg, lcv, mac)
    print("Assignments = ", MAC.nassigns)

    FC_CBJ = CSP(variables, domains, neighbors, constraints)
    csp_init_dom_wdeg(FC_CBJ)
    print("FC-CBJ:")
    fc_cbj(FC_CBJ, dom_wdeg, lcv, forward_checking)
    print("Assignments = ", FC_CBJ.nassigns)

    MIN_CONF = CSP(variables, domains, neighbors, constraints)
    print("MIN_CONF:")
    if not min_conflicts(MIN_CONF):
        print("None")
    print("Assignments = ", MIN_CONF.nassigns)

files = [
    "2-f24",
    "2-f25",
    "3-f10",
    "3-f11",
    "6-w2",
    "7-w1-f4",
    "7-w1-f5",
    "8-f10",
    "8-f11",
    "11",
    "14-f27",
    "14-f28"]

# RUN FOR ALL FILES

# for file in files:
#     solve(file)

# RUN FOR 1 FILE(You can change 'n' if u want)

n = 0
solve(files[n])