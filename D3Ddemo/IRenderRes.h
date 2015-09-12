/*!
 * \file IRenderRes.h
 *
 * \author puppet_master
 * \date 九月 2015
 *
 * \渲染资源的接口，所有可渲染的对象的资源基类
 */
#ifndef __IRENDERRES_H_
#define __IRENDERRES_H_

class IRenderRes
{
protected:
	LPDIRECT3DDEVICE9 m_pDevice;		    //D3D设备指针
	String m_filename;					    //资源名称（唯一标识符）
public:
	IRenderRes(LPDIRECT3DDEVICE9 device);
	virtual ~IRenderRes(void);

	//初始化资源
	virtual HRESULT Init(LPCTSTR filename) = 0;

	//根据世界矩阵渲染
	virtual void Render(const LPD3DXMATRIX matrix ) = 0;

	//根据屏幕坐标渲染
	//virtual void Render(int x, int y) = 0;

	void SetResourceName(LPCTSTR name);
	std::string GetResourceName()
	{
		return m_filename;
	}
};


#endif

