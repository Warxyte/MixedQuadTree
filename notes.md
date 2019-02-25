# SplitVisitor
Lorsque visit() accès concurrent : 
* new_pts (list<Point3D>) : var de la classe pour stocker les nouveaux pts créés 
* edges (set<QuadEdge>) : suppression et insertion d'éléments 
* points (vector<MeshPoint>) : accès en lecture 
* new_eles (vector<vector<unsigned int> >) : var de la classe pour stocker les nouveaux pts créés
* clipping (vector<vector<Point3D> >) : var de la classe pour stocker les nouveaux pts créés

# IntersectionsVisitor
Lorsque visit() accès concurrent : 
* select_edges (bool) :  
true, check avec des points spécifiques (-> coords & edges)  
false, check avec tous les points (-> points)
* ply (Polyline) : accès en lecture / copies
* quandrant->intersected_edges (list<unsigned int>) : accès lecture mais où est il modifié ?
* edges (list<unsigned int>) : accès en lecture
* coords (vector<Point3D>) : accès en lecture
* points (vector<MeshPoint>) : accès en lecture

Possible amélioration, dans visit, on renvoie true / false.  
Hors on réalise une boucle, ou l'on ajoute des éléments dans une liste puis on renvoie !liste.empty().  
Aucune modification n'est réalisé sur les données (?), on peut donc retourner un résultat avant de finir la boucle si on ajoute un élément.  


# Dans la première boucle

Variable **i** correspond au niveau de raffinement actuel.  
Variable **new_pts** permet de sortir de la première boucle :
- A chaque début d'itération elle est clear
- Est utilisé par le **SplitVisitor** qui lui ajoute des éléments.
- A chaque fin d'itération son contenu est ajouté à la variable **points (var de classe)**

**SplitVisitor** accès concurrent : 
* new_pts (list<Point3D>) : réinit après traitement en entier du quadrant (donc plusieurs itérations donc ajout de pts)
* edges (set<QuadEdge>) : container global
* points (vector<MeshPoint>) : container global
* new_eles (vector<vector<unsigned int> >) : réinit avant chaque appel
* clipping (vector<vector<Point3D> >) : réinit avant chaque appel
