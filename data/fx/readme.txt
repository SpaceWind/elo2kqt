This file defines SPRITE FORMAT



@.preload
spritename
myspriteAttachmentName
/.preload


@.
spritename
myspriteAttachmentName
/.

@spritename
	texture = {pic2.png}
	textureOffset = {0 0}
	frameSize = {70 70}
	transparentColor = {255 255 255}
	animation = {0 0 90000} as default
	animation = {0 0 80000} as nextAnimation
	attachment = {left top} as :mySpriteAttachmentName
	attachment = {left top} as notherAttachment
/spritename

@myspriteAttachmentName
	texture = {attachment.png}
	textureOffset = {0 0}
	frameSize = {70 70}
	transparentColor = {255 255 255}
/myspriteAttachmentName




getSprite("spritename");		//Возьмет весь спрайт со всеми аттачментами
getSprite(":spritename");		//Возьмет базовый спрайт без аттачментов
//если мы берем pure-вариант спрайта, ему нельзя уже выбрать конкретизацию аттачментов, так как их нет в спрайте

getSprite(:spritename+myspriteAttachmentName); // возьмет чистый spritename и добавит к нему новый спрайт-аттачмент, со всеми его аттачментами рекурсивно
getSprite(:spritename+:myspriteAttachmentName); //то же самое, но не рекурсивно



texture = pic2.png
textureOffset = {0 0} 
frameSize = {70 70}
transparentColor = {255 255 255}
animation = {0 0 90000} as default
animation = {0 0 80000} as nextAnimation
attachment = {myspriteAttachmentName left top}
attachment = {notherAttachment left top}

Как это должно получать доступ:

params.texture			|"pic2.png"
params.textureOffset		|"0" "1"
params.animation		|"default" "nextAnimation"
params.animation.default	|"0" "0" "90000"
params.attachment		|"{myspriteAttachmentName left top}" "{notherAttachment left top}"
params.attachment[0]		|"myspriteAttachmentName" "left" "top"
params.attachment[1]		|"notherAttachment" "left" "top"

params.:texture

1. Разбиваем строку по знаку =, получаем две строки - название переменной, и хвост. Парсим хвост.
2. Тримируем строку.
3. Ищем блок данных, он начинается на { и заканчивается на }. Строка между скобками - блок данных.
4. Создаем блок данных .paramName[i] и парсим блок данных на слова, забиваем. Где [i] - количество блоков данных для данного параметра
5. Парсим строку данных. Если найдено слово 'as', то следующее слово - это псевдоним
6. Если был найден псевдоним, ьл создаем блок данных .paramName.pseudoName и байндим это на распаршенные данные.
7. Дополняем блок данных .paramName распаршеным блоком данных, если нет псевдонима, либо самим псевдонимом.





























 