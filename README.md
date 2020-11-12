## Computer Graphics - P1

First Computer Graphics GLSL exercise.

Programing Basic Shaders, and additionally, working with Geometry.

Shaders not included in the repo (not yet :P)

# Basics
- [x] Define una matriz de proyección que conserve el aspect ratio cuando cambiamos el tamaño de la ventana.

- [x] Añade un nuevo cubo a la escena. El segundo cubo deberá orbitar alrededor del primero describiendo una circunferencia a la vez que rota sobre su eje Y.

- [x] Control de la cámara con el teclado (First Person Shooter). Controles mínimos que deberán incluirse: movimiento hacia adelante, retroceso, movimientos laterales (izquierda y derecha) y giros (izquierda y derecha).

- [x] Crear un shader de vértices y otro de fragmentos de forma que:

  - Cuando el índice de la primitiva (gl_PrimitiveID) sea impar, el color del fragmento este determinado por su normal en coordenadas de la cámara.
  - Cuando el índice de la primitiva (gl_PrimitiveID) sea par, se pinten las coordenadas de textura.
 
- [x] Crear un shader de vértices y otro de fragmentos de forma que se descarten algunos de los fragmentos de las caras del cubo. Nota: debes utilizar la sentencia discard.

  - [x] Opción 1: Crea una textura en blanco y negro. Asigna dicha textura al cubo que se ha usado en las prácticas. Descarta los fragmentos que tengan asociado el color negro.
  - [x] Opción 2: Descarta los fragmentos que no cumplan esta condición:
  ```
  (𝒓 − 𝟎. 𝟓)^𝟐 + (𝒔 − 𝟎. 𝟓)^2 < 𝟎.𝟐
  ```
  Nota: r y s son las coordenadas de textura del fragmento

# Optional
- [x] Controla el giro de la cámara utilizando el ratón (cámara orbital).

- [ ] Crea un tercer cubo y hazlo orbitar alrededor del primero. Define su movimiento utilizando curvas de Bézier, splines cúbicos o polinomios de interpolación de CatmullRom.

- [ ] Pinta alguna forma geométrica sobre las caras del cubo utilizando el shader de fragmentos. Nota: puedes utilizar las coordenadas de textura para asignar un valor numérico a cada fragmento.

- [ ] Crea un nuevo modelo y añádelo a la escena.

  - [ ] Opción 1: Define sus vértices manualmente.
  - [ ] Opción 2: Carga un fichero de un formato conocido. Puedes utilizar librerías auxiliares como ASSIMP (http://www.assimp.org/).

# TODO
- [ ] Create Entity-derived class (null object) to parent obejct to and deal with rotations and translations differently
