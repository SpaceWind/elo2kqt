ContextManager DEFINES

Получает размер внешней области рендера (внешней context), равный размеру окна.
Создает один раз QImage контекст отображения, размером равному ВНУТРЕННЕМУ размеру рендера.

При рендере context получает список RenderInfo QList<renderInfo>.
Также получает QRect который нужно рендериить.
Также получает струтуру по управлению скроллингом в зависимости от глубины.
Выглядит как:

@deepFunction
	movePoints = {2048 1024}
	movePoints = {-2048 0}
	movePoints = {-1024 840}
	scalePoints = {2048 1440}
	scalePoints = {1536 1024}
	scalePoints = {1024 1024}
	scalePoints = {512 1024}
	scalePoints = {0 768}
	scalePoints = {-1024 512}
	scalePoints = {-2048 0}
/deepFunction

									[]<- QRect OuterRect
									[]<- QRect InnerRect
QVector<RenderInfo> toRender 	<-  []<- QVector<RenderInfo> spriteWantedToRender


Проходимся по RenderInfo исходном массива
LeftOffset и topOffset нормализируем по movePoints
DestWidth и DestHeight нормализируем по ScalePoints

Вытаскиваем только те спрайты, которые попали в innerRect.

Вычисляем коэффициенты для рескейла 
widthCoef = OuterRect.width / innerRect.width
heightCoef  = OuterRect.height / innerRect.height

DestWidth и DestHeight нормализируем по widthCoef и heightCoef

Возвращаем получившиеся дескрипторы рендера.


