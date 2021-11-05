#!/usr/bin/env python3
import networkx as nx # graph implementation
import matplotlib.pyplot as plt # graph plot
import time # sleep(); just for debug

def plot_graph(g: nx.Graph, s, t, caminho_de_aumento) -> None:
  g_copy = g.copy()
  pos = nx.spring_layout(g, scale=5)

# nodes
  color_map = ['orange' if node == s or node == t else 'steelblue' for node in G]
  nx.draw_networkx_nodes(g, pos, node_size=250, node_color=color_map)

  for i, j in g.edges:
    g_copy.adj[i][j]['color'] = 'black'
  if caminho_de_aumento:
    for i in range(1, len(caminho_de_aumento)):
      g_copy.adj[caminho_de_aumento[i-1]][caminho_de_aumento[i]]['color'] = 'r'
      edge_colors = nx.get_edge_attributes(g_copy, 'color').values()
      nx.draw_networkx_edges(g, pos, width=2, arrowsize=10, edge_color=edge_colors, connectionstyle="arc3, rad=0.1")
  else:
    nx.draw_networkx_edges(g, pos, width=2, arrowsize=10, connectionstyle="arc3, rad=0.1")

# labels
  labels = nx.get_edge_attributes(g, 'c')
  labels2 = nx.get_edge_attributes(g, 'f')
  l = []
  l.append(labels)
  l.append(labels2)
  edge_labels = {}
  for u, v, data in g.edges(data=True):
    edge_labels[u, v] = data

  nx.draw_networkx_labels(g, pos, font_size=10, font_family='sans-serif')
  nx.draw_networkx_edge_labels(g, pos, edge_labels=edge_labels, font_size=14, label_pos=0.3)

  plt.rcParams['figure.figsize'] = [25, 20]
  plt.figure(3, figsize=(25,20), dpi=60)
  plt.show()

# Verifica se ha um caminho entre os nohs s e t, i.e., nohs que nao foram visitados
def bfs_verify_path(g: nx.Graph, s, t, visited_arg) -> bool:
  q = []
  visited = visited_arg.copy()
  visited.append(s)
  q.append(s)

  while q:
    tmp = q.pop(0)
    for neighbour in g.neighbors(tmp):
      if neighbour not in visited:
        visited.append(neighbour)
        q.append(neighbour)
    if tmp == t:
      return True

  return False

# Breadth first-search modificado
# Busca um caminho de aumento entre s e t em Gx = (V, Ax')
def bfs(g_arg: nx.Graph, s, t) -> []:
  g = g_arg.copy()
  visited = []
  q = []
  visited.append(s)
  q.append(s)

  ret = []
  while q:
    tmp = q.pop(0)
    if tmp == None:
      break
    tmp_max_node = None
    tmp_max_node_value = 0
    ret.append(tmp)
    for neighbour in g.neighbors(tmp):
      if neighbour not in visited:
        if bfs_verify_path(g, neighbour, t, visited): # if there is a path between current node and t
          dif = g.adj[tmp][neighbour]['c'] - g.adj[tmp][neighbour]['f']
          if dif > tmp_max_node_value:
            tmp_max_node = neighbour
            tmp_max_node_value = dif
    q.append(tmp_max_node)
    visited.append(tmp_max_node) 
    if tmp == t:
      return ret
  return []

# Algorithm 3: Incrementa-Fluxo
def incrementa_fluxo(G: nx.Graph, P: []) -> int:
  delta = 0 # delta := min{uij - x'ij, tal que (i, j) eh arco de P}
  for i in range (1, len(P)):
    temp = G.adj[P[i-1]][P[i]]["c"] - G.adj[P[i-1]][P[i]]["f"]
    if delta == 0 or temp < delta:
      delta = temp

  print("\tdelta:", delta, end="\n\n")

  for i in range (1, len(P)):
    G.adj[P[i-1]][P[i]]["f"] = G.adj[P[i-1]][P[i]]["f"] + delta
    G.adj[P[i]][P[i-1]]["f"] = G.adj[P[i]][P[i-1]]["f"] - delta

  return delta

# Retorna os vertices que são alcancaveis a partir do nó inicial (s)
def get_corte_minimo(g: nx.Graph, s) -> []:
  visited = []
  q = []
  visited.append(s)
  q.append(s)
  ret = []
  while q:
    tmp = q.pop(0)
    ret.append(tmp)
    if tmp == None:
      break
    for neighbour in g.neighbors(tmp):
      if neighbour not in visited:
        if g.adj[tmp][neighbour]['c'] - g.adj[tmp][neighbour]['f'] > 0:
          q.append(neighbour)
          visited.append(neighbour)
          
  return ret


# G = (V, E) with flow capacity c; source node 's'; sink node 't'
def ford_fulkerson_algo(G: nx.Graph, s, t) -> (int, nx.Graph):
  temp = nx.DiGraph()
  temp.add_edges_from(G.edges())

  # set flow values to 0
  for i, j in temp.edges:
    G.adj[i][j]["f"] = 0
    G.add_edge(j, i, c=G.adj[i][j]["c"], f=G.adj[i][j]["c"])

  fluxo_total = 0
  count = 1
  while True:
    print(count, "a iteracao", sep='')
    G_residual = nx.DiGraph()
    for i, j in G.edges:
      if G.adj[i][j]["f"] < G.adj[i][j]["c"]:
        G_residual.add_edge(i, j, c=G.adj[i][j]["c"], f=G.adj[i][j]["f"])
    #print(G_residual.edges(data=True))
    print("Grafo residual")
    plot_graph(G_residual, 's', 't', None)
    # P = bfs Busca um caminho de aumento entre s e t em Gx = (V, Ax')
    P = []
    if not nx.is_empty(G_residual):
      P = bfs(G_residual, s, t)
      if P:
        print("\ncaminho de aumento:", list(P))
        plot_graph(G_residual, 's', 't', list(P))

    if P: # if P existe then
      fluxo_total += incrementa_fluxo(G, P)
    else: # until nao exista caminho P
      break
    count = count + 1
    print("\n\n")

  # Corte minimo T. Conjunto de nos acessiveis a partir de s no grafo residual de fluxo maximo.
  T = get_corte_minimo(G_residual, s)

  return fluxo_total, T
  

if __name__ == "__main__":
  G = nx.DiGraph()
  G.add_edge('s', 'v1', c=10)
  G.add_edge('s', 'v2', c=10)
  G.add_edge('v1', 'v2', c=2)
  G.add_edge('v1', 'v3', c=4)
  G.add_edge('v1', 'v4', c=8)
  G.add_edge('v2', 'v4', c=9)
  G.add_edge('v3', 't', c=10)
  G.add_edge('v4', 'v3', c=6)
  G.add_edge('v4', 't', c=10)

  x, t = ford_fulkerson_algo(G, 's', 't')
  print("fluxo maximo =", x)
  print("corte minimo ={", t, "}", sep="")
