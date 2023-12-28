// 引入 Bullet.h 头文件
#include "Bullet.h"

// 构造函数，初始化子弹速度为 0
CBullet::CBullet()
	: m_nSpeed(0)
{
}

// 析构函数
CBullet::~CBullet()
{
}

// 初始化子弹数据的方法，接受一个包含子弹数据的结构体 SBulletDt 指针
bool CBullet::initWithData(SBulletDt* pData)
{
	// 使用 Cocos2d-x Node 的初始化方法
	if (!Node::init()) {
		return false;
	}

	// 从传入的数据结构体中获取子弹 ID 和速度
	m_nBulletID = pData->nID;
	m_nSpeed = pData->nSpeed;

	// 使用第一张图片创建 Sprite，并添加到当前 Node
	m_pImage = Sprite::createWithSpriteFrameName(pData->VecImgs[0]);
	this->addChild(m_pImage);

	// 创建爆炸动画
	this->createBoomAnims();

	// 初始化成功
	return true;
}

// 创建一个子弹对象并返回，接受一个包含子弹数据的结构体 SBulletDt 指针
CBullet* CBullet::createWithData(SBulletDt* pData)
{
	// 创建子弹对象
	CBullet* pBullet = new CBullet();

	// 如果创建成功并且初始化成功，自动释放对象并返回
	if (pBullet && pBullet->initWithData(pData)) {
		pBullet->autorelease();
		return pBullet;
	}

	// 创建失败或初始化失败时，释放对象并返回空指针
	CC_SAFE_DELETE(pBullet);
	return nullptr;
}

// 每帧更新方法，用于移动子弹、检测碰撞等
void CBullet::update(float delta)
{
	// 判断子弹类型是否为特定类型，如果是，则执行相应逻辑
	if (m_nBulletID == 5001 || m_nBulletID == 5004 || (m_nBulletID >= 5010 && m_nBulletID <= 5012)) {
		// 如果没有目标，直接返回
		if (!m_pTarget) {
			return;
		}

		// 获取目标位置和当前位置
		Vec2 EnemyPos = m_pTarget->getPosition();
		Vec2 pos = this->getPosition();

		// 计算子弹移动方向并更新位置
		m_vDir = (EnemyPos - pos).getNormalized();
		pos += (m_vDir * m_nSpeed * delta);
		this->setPosition(pos);

		// 计算子弹和目标之间的距离
		float fDisSq = EnemyPos.getDistanceSq(pos);

		// 如果距离小于等于 5 的平方，则认为发生碰撞
		if (fDisSq <= 5 * 5) {
			// 处理碰撞
			// 执行碰撞回调函数
			m_CollisionCb(this);
		}
	}
}

// 设置子弹的目标节点
void CBullet::setTarget(Node* target)
{
	m_pTarget = target;
	// 开启每帧更新
	this->scheduleUpdate();
}

// 添加碰撞回调函数，传入一个函数对象作为回调
void CBullet::addCollsionCb(std::function<void(CBullet*)> Cb)
{
	m_CollisionCb = Cb;
}

// 创建爆炸动画
void CBullet::createBoomAnims()
{
	// 从配置管理器获取子弹的爆炸效果数据
	SEffectDt* pData = static_cast<CEffectDtMgr*>(CConfigMgr::getInstance()->getData("EffectDtMgr"))->getDataByObjectID(m_nBulletID);

	// 获取精灵帧缓存实例
	SpriteFrameCache* pCache = SpriteFrameCache::getInstance();

	// 创建爆炸动画对象
	m_pAnimaBoom = Animation::create();

	// 遍历子弹爆炸效果的图片，添加到动画中
	for (int i = 0; i < pData->VecImgs.size(); i++) {
		SpriteFrame* pFrame = pCache->getSpriteFrameByName(pData->VecImgs[i]);
		m_pAnimaBoom->addSpriteFrame(pFrame);
	}

	// 设置动画每帧的播放间隔
	m_pAnimaBoom->setDelayPerUnit(0.1);

	// 对动画进行引用计数，防止被释放
	m_pAnimaBoom->retain();
}

// 获取子弹在世界坐标系中的包围盒
Rect CBullet::getBoundingBoxToWorld()
{
	// 获取子弹图片的包围盒
	Rect rcImg = m_pImage->getBoundingBox();

	// 创建一个矩形对象，表示子弹在世界坐标系中的包围盒
	Rect rc;
	rc.size = rcImg.size;
	rc.origin = this->convertToWorldSpaceAR(rcImg.origin);
	return rc;
}
