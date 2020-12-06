# Modelo Simples de Propagação em Redes

### Rede Regular com grau 2
### Modelo com tempo, estado e espaço discretos
### Transmissão Estocástica



```python
import numpy as np
import matplotlib.pyplot as plt
import random

N = 100

# np.random.random_sample()

```

## Geração da Rede


```python
matriz = np.zeros((N,N), dtype=int)

for i in range(N-1):
    matriz[i,i+1] = 1
    matriz[i+1,i] = 1
#fechamento do laço (ligando o primeiro nó ao último)
matriz[0,N-1] = 1
matriz[N-1,0] = 1
#print(matriz[10])
    
#plt.matshow(matriz)
#plt.show()
```

## Dinâmica (Propagação)


```python
estado = np.zeros((N), dtype=int)
duracao = np.zeros((N), dtype=int)

T = 100
D = 5
prob = 0.5

for i in range(1, 10):
  estado[random.randint(1, 90)] = 1 # contaminacao se inicia no vértice 10
  duracao[random.randint(1, 90)] = D
fig, axis = plt.subplots()
axis.imshow(np.vstack((estado,estado)), aspect='auto', vmin=0, vmax=1, cmap='coolwarm')
axis.set_axis_off()
fig.subplots_adjust(top=1, bottom=0.01, left=0, right=5)
fig.text(0,0.5, "T: %04d"%(0), va='center', ha='right', fontsize=50)
plt.show()

for t in range(1,T):
    new_estado = np.zeros((N), dtype=int)
    for n in range(N):

        if duracao[n] > 0:
            duracao[n] -= 1 # time-step
     
        indices = np.where(matriz[n,:]==1)[0] # lista de adjacência nó n
        viz_contaminado = False
        print(np.where(matriz[n,:]==1))
        for idx in indices:
            if estado[idx] == 1: # vizinho está doente
                viz_contaminado = True
                break

        if np.random.random_sample()<=prob and viz_contaminado: # chance de contágio    
                new_estado[n] = 1
                duracao[n] = D
        else:
            if duracao[n] == 0:
                new_estado[n] = 0
            else:
                new_estado[n] = estado[n]

    estado = new_estado
    fig, axis = plt.subplots()
    axis.imshow(np.vstack((estado,estado)), vmin=0, vmax=1, aspect='auto', cmap='coolwarm')
    axis.set_axis_off()
    fig.subplots_adjust(top=1, bottom=0.01, left=0, right=5)
    fig.text(0,0.5, "T: %04d"%(t), va='center', ha='right', fontsize=50)
#     fig.text(0,0,"Tempo", name, va='center', ha='right', fontsize=10)

    plt.show()
    if len(np.nonzero(estado)[0]) == 0:
        break
    

```


![png](./images/output_5_0.png)

![png](./images/output_5_2.png)

![png](./images/output_5_4.png)

![png](./images/output_5_6.png)

![png](./images/output_5_8.png)

![png](./images/output_5_10.png)

![png](./images/output_5_12.png)

![png](./images/output_5_14.png)

![png](./images/output_5_16.png)

![png](./images/output_5_18.png)

![png](./images/output_5_20.png)

![png](./images/output_5_22.png)

![png](./images/output_5_24.png)

![png](./images/output_5_26.png)

![png](./images/output_5_28.png)

![png](./images/output_5_30.png)

![png](./images/output_5_32.png)

![png](./images/output_5_34.png)

![png](./images/output_5_36.png)

![png](./images/output_5_38.png)

![png](./images/output_5_40.png)

![png](./images/output_5_42.png)

![png](./images/output_5_44.png)

![png](./images/output_5_46.png)

![png](./images/output_5_48.png)

![png](./images/output_5_50.png)

![png](./images/output_5_52.png)

![png](./images/output_5_54.png)

![png](./images/output_5_56.png)

![png](./images/output_5_58.png)

![png](./images/output_5_60.png)

![png](./images/output_5_62.png)

![png](./images/output_5_64.png)

![png](./images/output_5_66.png)

![png](./images/output_5_68.png)

![png](./images/output_5_70.png)

![png](./images/output_5_72.png)

![png](./images/output_5_74.png)

![png](./images/output_5_76.png)

![png](./images/output_5_78.png)

![png](./images/output_5_80.png)

![png](./images/output_5_82.png)

![png](./images/output_5_84.png)

![png](./images/output_5_86.png)

![png](./images/output_5_88.png)

![png](./images/output_5_90.png)

![png](./images/output_5_92.png)

![png](./images/output_5_94.png)

![png](./images/output_5_96.png)

![png](./images/output_5_98.png)

![png](./images/output_5_100.png)

![png](./images/output_5_102.png)

![png](./images/output_5_104.png)

![png](./images/output_5_106.png)

![png](./images/output_5_108.png)

![png](./images/output_5_110.png)

![png](./images/output_5_112.png)

![png](./images/output_5_114.png)

![png](./images/output_5_116.png)

![png](./images/output_5_118.png)

![png](./images/output_5_120.png)

![png](./images/output_5_122.png)

![png](./images/output_5_124.png)

![png](./images/output_5_126.png)

![png](./images/output_5_128.png)

![png](./images/output_5_130.png)

![png](./images/output_5_132.png)

![png](./images/output_5_134.png)

![png](./images/output_5_136.png)

![png](./images/output_5_138.png)

![png](./images/output_5_140.png)

![png](./images/output_5_142.png)

![png](./images/output_5_144.png)

![png](./images/output_5_146.png)

![png](./images/output_5_148.png)

![png](./images/output_5_150.png)

![png](./images/output_5_152.png)

![png](./images/output_5_154.png)

![png](./images/output_5_158.png)

![png](./images/output_5_160.png)

![png](./images/output_5_162.png)

![png](./images/output_5_164.png)

![png](./images/output_5_166.png)

![png](./images/output_5_168.png)

![png](./images/output_5_170.png)

![png](./images/output_5_172.png)

![png](./images/output_5_174.png)

![png](./images/output_5_176.png)

![png](./images/output_5_178.png)

![png](./images/output_5_180.png)

![png](./images/output_5_182.png)

![png](./images/output_5_184.png)

![png](./images/output_5_186.png)

![png](./images/output_5_188.png)

![png](./images/output_5_190.png)

![png](./images/output_5_192.png)

![png](./images/output_5_194.png)

![png](./images/output_5_196.png)

![png](./images/output_5_198.png)

