# Cacho-Alalay-FGF

Mi implementación de un algoritmo voraz para un jugador automático de Cacho Alalay en C++.

### Building the Project

You can build both the core simulation and the Web API from the root directory:

```bash
make
```

Alternatively, you can build them individually:

```bash
# To build the standalone simulation
cd src
make

# To build the Web API
cd api
make
```

## 🎲 Running simulations

The `src/cacho` executable runs a game between automated players (Random).

```bash
cd src
./cacho
```

## 🌐 Running the Web API

The `api/cacho_api` executable starts a server on `http://localhost:8080`.

```bash
cd api
./cacho_api
```

Once running, open [http://localhost:8080](http://localhost:8080) in your browser to play.

## 🛠 Features

- **Decoupled Engine**: Pure C++ implementation with no external dependencies (except for Crow/Boost in the API).
- **Alalay Rules**: Full support for Alalay tournament rules.
- **Web Interface**: Modern web client for human play.
- **Random Player**: Included for testing and simulation.
- **Human Player**: Base class and logic for human interaction.

## Algunas anotaciones matemáticas detrás del juego

Sea $n = 5$ (número total de dados lanzados) y $p = \frac{1}{6}$ (probabilidad de obtener un número específico). La probabilidad de obtener exactamente $k$ aciertos se define por distribución binomial:

$$
P(X=k) = \binom{n}{k} p^k (1-p)^{n-k}
$$

### Resultados para cada jugada, calculados:

**Para $k=0$ (ningun tipo de mano)**

$$
P(X=0) = \binom{5}{0} \left(\frac{1}{6}\right)^0 \left(\frac{5}{6}\right)^5 = \frac{3125}{7776} \approx 40.18\%
$$

**Para $k=1$:**

$$
P(X=1) = \binom{5}{1} \left(\frac{1}{6}\right)^1 \left(\frac{5}{6}\right)^4 = \frac{3125}{7776} \approx 40.18\%
$$

**Para $k=2$:**

$$
P(X=2) = \binom{5}{2} \left(\frac{1}{6}\right)^2 \left(\frac{5}{6}\right)^3 = \frac{1250}{7776} \approx 16.07\%
$$

**Para $k=3$:**

$$
P(X=3) = \binom{5}{3} \left(\frac{1}{6}\right)^3 \left(\frac{5}{6}\right)^2 = \frac{250}{7776} \approx 3.21\%
$$

**Para $k=4$: (este es importante, junto a k=5, ambos suman 0,33%)**

$$
P(X=4) = \binom{5}{4} \left(\frac{1}{6}\right)^4 \left(\frac{5}{6}\right)^1 = \frac{25}{7776} \approx 0.32\%
$$

**Para $k=5$:**

$$
P(X=5) = \binom{5}{5} \left(\frac{1}{6}\right)^5 \left(\frac{5}{6}\right)^0 = \frac{1}{7776} \approx 0.01\%
$$
