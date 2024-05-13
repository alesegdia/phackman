#pragma once


class PersistentData
{
public:
	static PersistentData Instance;

	void Reset()
	{
		m_currentFloor = 1;
	}

	void AdvanceFloor()
	{
		m_currentFloor++;
	}

	int GetCurrentFloor()
	{
		return m_currentFloor;
	}

private:
	PersistentData()
	{
		Reset();
	}

	int m_currentFloor = 1;

};

