/*
TODO 
struttura base
tipo, nome, val iniziale

nel caso funzione
tipo, (*nome),parametri, funzione 
risolto creando un'altra macro per le funzioni
# crea una stringa con il parametro passato nome -> "nome" 
## concatena parametro passato e elemento da concatenare nome##_id -> nome_id non valido per concatenare operatori come nome##->elemento 
*/

MEMBER(int,id,10,())
MEMBER(char*,nome,"MM",())
FUNC(int,func,p,(int,int))
FUNC(void,init,init,(struct Gest *))
FUNC(int,lengthStr,lengthStr,(const char *))
FUNC(struct Gest*,str,str,(struct Gest *,const char *))


