#include "Button.h"
#include "UIManager.h"

Button::Button() :UIElement(Play::Point2D(0, 0), 0, 0)
{
	
}

Button::Button(float x, float y, short height, short width, const char* spriteName, FunctionType OnClickHandler, const char* btnName):UIElement(Play::Point2D(x, y), height, width)
{
	m_spriteName = spriteName;
	m_btnText = btnName;
	m_OnClickHandler = OnClickHandler;
}

Button::Button(Play::Point2f pos,  short height, short width,  const char* spriteName, FunctionType OnClickHandler, const char* btnName):UIElement(pos.x,pos.y, height, width)
{
	m_spriteName = spriteName;
	m_btnText = btnName;
	m_OnClickHandler = OnClickHandler;
}

void Button::SetSpriteName(const char* name)
{
	m_spriteName = name;
}

void Button::Render()
{
	//Scale from the defined height and width
	if (std::strcmp(m_spriteName, "") != 0)
		m_scale = static_cast<float>(m_height) / Play::GetSpriteHeight(m_spriteName);

	Play::Matrix2D rotMt = Play::MatrixRotation(Play::DegToRad(m_rot));

	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scale * m_hoverScale,0.0f,0.0f },
		{ 0.0f,m_scale * m_hoverScale,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(m_spriteName), scaleMt * rotMt, 0);
	//DEBUG UI
	DrawBoundingBox();
}

bool Button::OnDrag()
{
	if (!isActive)
		return false;
	return UIElement::OnDrag();
}

bool Button::OnHover()
{
	if (!isActive)
		return false;

	if (UIElement::OnHover())
	{
		m_hoverScale = 1.15f;
		m_OnHoverHandler();
		return true;
	}
	else
	{
		m_hoverScale = 1.0f;
		return false;
	}
}
bool Button::OnClick()
{
	if (!isActive)
 		return false;

	if (UIElement::OnClick())
	{
		m_OnClickHandler();
		return true;
	}
	return false;
}

void Button::AddOnClickHandler(FunctionType fun)
{
	m_OnClickHandler = fun;
}

void Button::AddOnHoverHandler(FunctionType fun)
{
	m_OnHoverHandler = fun;
}


