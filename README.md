# Proyecto-Final-Lab2
Diario de proyecto:

20/10 Damos por iniciado el proyecto, creamos repositorio git y empezamos a planificar cómo vamos a llevar a cabo el proyecto y cómo vamos a dividir tareas. Desarrollamos funciones básicas para el manejo de clientes, y organizamos el proyecto en diferentes librerías.

22/10 De a poco vamos estructurando el proyecto, nos costó bastante porque es la primera vez que trabajamos con estructuras compuestas, hicimos funciones básicas de clientes y nos guiamos con las estructuras que nos dio el profesor. Todavía tenemos muchas dudas de cómo emplear las fechas.

23/10 Agregamos la estructura de PracticaxIngresos y la añadimos a los nodos correspondientes. Formamos un diagrama para anotar las tareas que tenemos pendientes en el proyecto.

24/10 Creamos la funcion validarFechas para ser usada en fechas de ingreso y retiro, también creamos validarFechasPosteriores, que valida que las fechas de retiro sean posteriores a las de ingreso. Creamos algunas funciones básicas para la estructura de PracticaxIngresos. Terminamos la función alta ingreso, que requirió muchas validaciones, realizando también funciones auxiliares de la struct Ingresos. Determinamos que luego de cargar las listas de ingresos y de pxi, debíamos cargar la información en los archivos.

26/10 Hicimos funciones de Archivos de Pacientes, validación de Edad, Alta de Paciente con todos sus casos posible como, paciente existe y paciente existente pero dado de baja y por último hicimos la función de dar de baja un paciente, verificando que este exista, este dado de alta y no tenga ingresos cargados.

28/10 Arreglamos errores de duplicación de registros en el archivo, en la función cambiarEliminadoPaciente

1/11 Realizamos todas las funciones principales de prácticas, corrigiendo errores encontrados en el testeo.

5/11 Creamos la función baja Ingreso con sus respectivas funciones auxiliares, pero nos encontramos con un error en la función buscar Ingreso que no pudimos solucionar. Esperamos desarrollar otras funciones para lograr solucionarlo. 

6/11 Empezamos las funciones para crear el árbol y las listas a partir de los archivos. Solucionamos algunos errores que se daban en la función alta ingreso y en buscar paciente. Nos quedó por solucionar un error al mostrar todos los ingresos de un paciente, que probablemente se dé en alguna función auxiliar de la creación de las listas.

7/11 En el día de hoy determinamos que el error estaba en los DNI en los ingresos, por eso la función de crear el árbol solo cargaba los pacientes y no sus respectivos ingresos. Utilizamos demasiados printfs para nuestro gusto para encontrar el error, se pisaban datos no sabemos porque, empleamos fflush(stdin) y tampoco. Recurrimos a la IA y nos ayudó con alguna que otra validación más, pero no logró resolver el problema. La única solución que encontramos es alterar el orden de los campos en la declaración de las estructuras.
Queda pendiente testeo de la función recolectar datos los archivos y armar la estructura.

8/11 Hoy solucionamos errores en varias funciones de mostrar, que al iterar en las listas de ingresos, se modificaba la lista real, lo que producía que desaparezcan ingresos y pxi. Lo hicimos empleando variables auxiliares en cada lista. También solucionamos un error al eliminar un nodo de la lista de ingresos, la función estaba mal estructurada y hacía que no se termine la ejecución de bajaIngreso. Hicimos mejoras al mostrar ingresos y prácticas asociadas y mejoramos el manejo de memoria en la función cargarIngreso, con la intención de no tener problemas con la carga de datos.

9/11 En el día de la fecha terminamos de codear y testear el AMB de ingresos, descubrimos que dando de baja un paciente perdíamos gran parte del árbol. Luego testeando nos dimos cuenta que el strcmp no tiene en cuenta la cantidad de dígitos, vimos que comparando 8 y 222222, retornaba que el 8 era mayor, por lo tanto nos arruinaba la búsqueda binaria. Lo solucionamos creando la función dnicmp, la cual compara las longitudes antes de usar strcmp. Usando el archivo de prácticas del campus, teníamos varios errores ya que los nombres de las prácticas superan la dimensión máxima establecida, por lo que decidimos continuar usando un archivo propio. Empezamos la función de modificar PxI, y también creamos una función para buscar los nombres de las prácticas en el archivo mediante el id.

13/11 Hoy terminamos la función modificar PxI y la testeamos. Solucionamos errores al mostrar información, dados por malas llamadas a archivos, y por ciertos detalles en prints que hacían perder legibilidad. Estos errores también se veían reflejados en la función de alta Ingreso, pero ya no existen.También codeamos baja Pxi pero no la testeamos. Decidimos que todo el ABM de PxI se debe encontrar en el menú de Ingresos, ya que están sumamente ligados, y creemos que la modificación y la baja de PxI se deben hacer en el ámbito de modificar un ingreso.

14/11 El testeo de baja PXI fue algo complicado ya que no sabíamos por donde encarar su baja, eliminarlo de la lista es lo básico pero a nivel persistencia en archivo no sabíamos como hacerlo ya que no tiene la clásica baja lógica entonces decidimos multiplicar su número de ingreso por (-1) entonces el dia de mañana sabemos a qué ingreso pertenecía, pero el árbol no levanta ese dato al  iniciarse el programa.

15/11 Tuvimos que agregar el caso de que si se eliminan todas sus prácticas se de baja el ingreso ya que este quedaría vacío y sin sentido. El problema que se nos planteó fue que al swich de modificar Ingreso se rompía ya que se daba de baja el ingreso y elimina de la lista. 
Por lo tanto no se puede seguir editando algo que está eliminado. El error está casi resuelto.

16/11 Hoy terminamos de testear baja PxI, además agregamos una validación en modificar PxI y en alta Lista PxI para que no se puedan cargar prácticas repetidas en un mismo ingreso. Luego de testear eso codeamos por completo el ABM de empleados, en una nueva librería, y creamos otra librería más para los menús en la cual empezamos el menú principal y movimos el menú de admin el cual ya estaba casi finalizado. Nos pareció pertinente usar el dni en vez del nombre de usuario, ya que conocemos muchas aplicaciones que lo hacen de esta manera, y además nos pareció algo más amigable para el usuario. Decidimos que cuando el administrador carga un nuevo empleado, se le asigna una contraseña automáticamente que luego puede cambiar.

17/11 Hoy creamos la librería mostrar para contener todas las funciones de mostrar de las otras librerías y además agregar las funciones adicionales ahí. Creamos funciones adicionales para mostrar ingresos(por fecha y por id) y creamos la función de cambiar contraseña para el usuario. Además creamos algunos sub menus, pacientes Administrativos, ingresos Administrativos, el de mostrar paciente, el de mostrar ingresos y el de ajustes, en donde se puede cambiar nombre, apellido y contraseña del empleado. Queda pendiente hacer algunas funciones adicionales y hacer por completo el menú Profesionales.

19/11 Terminamos el menú ajustes dentro del menú de administrativo, testeamos inicios de sesión, pulimos printfs, descubrimos un error de parámetros en validarFechaPosterior y dejamos planteado el menuProfesional para hacerlo mañana.
