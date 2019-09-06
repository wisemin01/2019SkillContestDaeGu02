#pragma once
#include "Renderer.h"

class Font;

class TextRenderer :
	public Renderer
{
private:
	OutputString m_sContext;
	Color m_Color = Color::White;

	Font* m_pFont = nullptr;
public:

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void Render();

	void Set(const string& fontKey, int fontSize, const OutputString& context, Color color = Color::White);
	void SetContext(const OutputString& context);
};

