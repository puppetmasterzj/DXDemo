/*!
 * \file IRenderRes.h
 *
 * \author puppet_master
 * \date ���� 2015
 *
 * \��Ⱦ��Դ�Ľӿڣ����п���Ⱦ�Ķ������Դ����
 */
#ifndef __IRENDERRES_H_
#define __IRENDERRES_H_

class IRenderRes
{
protected:
	LPDIRECT3DDEVICE9 m_pDevice;		    //D3D�豸ָ��
	String m_filename;					    //��Դ���ƣ�Ψһ��ʶ����
public:
	IRenderRes(LPDIRECT3DDEVICE9 device);
	virtual ~IRenderRes(void);

	//��ʼ����Դ
	virtual HRESULT Init(LPCTSTR filename) = 0;

	//�������������Ⱦ
	virtual void Render(const LPD3DXMATRIX matrix ) = 0;

	//������Ļ������Ⱦ
	//virtual void Render(int x, int y) = 0;

	void SetResourceName(LPCTSTR name);
	std::string GetResourceName()
	{
		return m_filename;
	}
};


#endif

