{-
NOTA: DESAPROBADO
Ejercicio 1: M
Ejercicio 2: R
Ejercicio 3: B
Ejercicio 4: M+
Ejercicio 5: M
-}

--Empezamos utilizando la definicion de esprimo vista en la clase5

menordiv::Integer->Integer
menordiv n = menordivdesde n 2

menordivdesde::Integer->Integer->Integer
menordivdesde n k | mod n k == 0 = k
                  | otherwise = menordivdesde n (k+1)
                  
                  
esprimo ::Integer->Bool
esprimo 1 = False
esprimo n = n == menordiv n 
          
--Como los a-pseudoprimos nos piden un n compuesto, tenemos que definir "compuestos", que no es otra cosa que el opuesto de "esprimo"
          
compuestos::Integer->Bool
compuestos n = not (esprimo n)
          

--Buscamos sonCoprimos, para esto le ponemos 2 condiciones:
-- 1. que sus componentes (n , m) sean primos
-- 2. que m divida a n^(m-1)-1

sonCoprimos::Integer->Integer->Bool
sonCoprimos n m | esprimo n && esprimo m && mod (n^(m-1)-1) m == 0 = True
                | otherwise = False
-- ¡MAL! Dos números son coprimos si no comparten divisores
--o lo que es lo mismo, su MCD es 1

--Muy parecido con "sonCoprimos", solo que esta vez tienen que cumplir que:
-- 1. n sea compuesto
-- 2. n divida a 2^(n-1)-1

es2Pseudoprimo::Integer->Bool
es2Pseudoprimo n | compuestos n && mod (2^(n-1)-1) n == 0 = True
                 | otherwise = False
--REGULAR. Estás permitiendo que 1 sea 2-pseudoprimo
--"es3pseudoprimo" es exactamente lo mismo a su predecesor, solo que cambiando la ecuacion a 3^(n-1)-1


es3Pseudoprimo::Integer->Bool
es3Pseudoprimo n | compuestos n && mod (3^(n-1)-1) n == 0 = True
                 | otherwise = False
--Ídem. Estás permitiendo que 1 sea 2-pseudoprimo

--Aca, buscamos cuantos 3-pseudoprimos hay entre un rango de 1 a m. Para esto definimos por recurrencia que empiece desde m y cada vez que encuentre un 3-pseudoprimo, sume 1, hasta llegar a 1

cantidad3Pseudoprimos::Integer->Integer
cantidad3Pseudoprimos m | m == 1 = 0 --Claro, lo terminás salvando acá
                        | es3Pseudoprimo m == True = cantidad3Pseudoprimos (m-1) + 1
                        | es3Pseudoprimo m == False = cantidad3Pseudoprimos (m-1) + 0
--BIEN-

 
--Para los dos ultimos, no logre programarlos debidamente.


-- En kesimo2y3Pseudoprimo intente hacer al revez que cantidad3Pseudoprimos, es decir, que encontrara cuantos kesimo2y3Pseudoprimos hay entre 1 y n, y despues que devolviera el valor del mas cercano a k. 

--Para eso, programe "kesimo" que devuelve la cantidad de kesimo2y3Pseudoprimos de 1 a n

kesimo::Integer->Integer
kesimo n | n == 1 = 0
         | es3Pseudoprimo n && es2Pseudoprimo n == True = kesimo (n-1) + 1
         | otherwise = kesimo (n-1) + 0 -- ¿Por qué le sumás 0?
--Va por este lado

--E intenté (sin resultado) que me devuelva el ultimo numero obtenido por kesimo 
--MAL+
kesimo2y3Pseudoprimo::Integer->Integer
kesimo2y3Pseudoprimo 1 = 1
kesimo2y3Pseudoprimo n | n == kesimo n = n
                       | otherwise = kesimo2y3Pseudoprimo (n-1)
           
--Aca directamente no logre avanzar mucho, ya que no logre plantear bien el problema.
--Ok, fijate para empezar, ¿qué debería devolver esCarmichael?
esCarmichael::Integer->Integer
esCarmichael 0 = 0
esCarmichael n | compuestos n && mod (n^(n-1)-1) n == 1 = 0
               | esCarmichael n /= 1 = n 
--MAL