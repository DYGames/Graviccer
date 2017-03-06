#include "Singleton.h"

Singleton* Singleton::m_uInstance = 0;
Singleton* Singleton::getInstance()
{
	if (!m_uInstance)
		m_uInstance = new Singleton;

	return m_uInstance;
}