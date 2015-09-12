/*!
 * \file Picking.h
 *
 * \author puppet_master
 * \date ���� 2015
 *
 * \ʰȡ������
 * \���裺1.���ݶ�ά�����Լ�������������ͶӰ����
 * \	  2.������ת����ģ�͵�����ϵ��
 * \	  3.�������ж������յõ�ʰȡ�Ķ���
 * \
 * \�������߾�̬��
 */
#ifndef __PICKING_H_
#define __PICKING_H_

//���߽ṹ��
struct Ray
{
	D3DXVECTOR3 m_vOrigin;			//���
	D3DXVECTOR3 m_vDirection;		//����

	//���캯��(Ĭ�ϳ�ʼ��Ϊ0������Ϊ��Z������)
	Ray(const D3DXVECTOR3& origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f), const D3DXVECTOR3& direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f)) : m_vOrigin(origin), m_vDirection(direction)
	{ 

	}
};

//��Χ��ṹ��
struct BoundingSphere
{
	D3DXVECTOR3 m_vCenter;			//�е�
	float		m_fRadius;			//�뾶

	//���캯��
	BoundingSphere(const D3DXVECTOR3& center = D3DXVECTOR3(0.0f, 0.0f, 0.0f), float radius = 1.0f) : m_vCenter(center), m_fRadius(radius)
	{

	}
}; 


//ʰȡ�����
class Picking
{
private:
	IDirect3DDevice9*   m_pDevice;			//D3D�豸
public:
	Picking(IDirect3DDevice9* device);
	~Picking(void);

	//����ʰȡ���ߣ�����Ϊ����ڴ����е����꣬���Ϊһ��δ�����任�����ߣ�ͨ��ָ�봫�Σ����سɹ����
	void CalculatePickingRay(int x, int y, Ray* ray);
	
	//�����߽��б任
	void TransformRay(Ray* ray, D3DXMATRIX* matrix);

	//�жϰ�Χ��������Ƿ��ཻ
	bool Ray_SphereIntersect(const Ray* ray, const BoundingSphere* sphere);

	//�ṩ�����Ľӿڣ������������&�����Χ��ָ�룬�ж��Ƿ��ཻ
	bool IsPicked(int x, int y, const BoundingSphere* sphere);
};
#endif


