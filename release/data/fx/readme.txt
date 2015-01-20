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




getSprite("spritename");		//������� ���� ������ �� ����� ������������
getSprite(":spritename");		//������� ������� ������ ��� �����������
//���� �� ����� pure-������� �������, ��� ������ ��� ������� ������������� �����������, ��� ��� �� ��� � �������

getSprite(:spritename+myspriteAttachmentName); // ������� ������ spritename � ������� � ���� ����� ������-���������, �� ����� ��� ������������ ����������
getSprite(:spritename+:myspriteAttachmentName); //�� �� �����, �� �� ����������



texture = pic2.png
textureOffset = {0 0} 
frameSize = {70 70}
transparentColor = {255 255 255}
animation = {0 0 90000} as default
animation = {0 0 80000} as nextAnimation
attachment = {myspriteAttachmentName left top}
attachment = {notherAttachment left top}

��� ��� ������ �������� ������:

params.texture			|"pic2.png"
params.textureOffset		|"0" "1"
params.animation		|"default" "nextAnimation"
params.animation.default	|"0" "0" "90000"
params.attachment		|"{myspriteAttachmentName left top}" "{notherAttachment left top}"
params.attachment[0]		|"myspriteAttachmentName" "left" "top"
params.attachment[1]		|"notherAttachment" "left" "top"

params.:texture

1. ��������� ������ �� ����� =, �������� ��� ������ - �������� ����������, � �����. ������ �����.
2. ��������� ������.
3. ���� ���� ������, �� ���������� �� { � ������������� �� }. ������ ����� �������� - ���� ������.
4. ������� ���� ������ .paramName[i] � ������ ���� ������ �� �����, ��������. ��� [i] - ���������� ������ ������ ��� ������� ���������
5. ������ ������ ������. ���� ������� ����� 'as', �� ��������� ����� - ��� ���������
6. ���� ��� ������ ���������, �� ������� ���� ������ .paramName.pseudoName � ������� ��� �� ������������ ������.
7. ��������� ���� ������ .paramName ����������� ������ ������, ���� ��� ����������, ���� ����� �����������.





























 