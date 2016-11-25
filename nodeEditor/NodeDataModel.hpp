#pragma once

#include <memory>

#include <QtWidgets/QWidget>

#include "PortType.hpp"
#include "NodeData.hpp"
#include "Serializable.hpp"

#include "Export.hpp"

#include "nodes/DistanceFieldData.hpp"

class NODE_EDITOR_PUBLIC NodeDataModel
  : public QObject
  , public Serializable
{
  Q_OBJECT

public:

  virtual
  ~NodeDataModel() {}

  /// Caption is used in GUI
  virtual QString
  caption() const = 0;

  /// It is possible to hide caption in GUI
  virtual bool
  captionVisible() const { return true; }

public:

  virtual
  unsigned int
  nPorts(PortType portType) const = 0;

  virtual
  NodeDataType
  dataType(PortType portType, PortIndex portIndex) const = 0;

public:

  /// Triggers the algorithm
  virtual
  void
  setInData(std::shared_ptr<NodeData> nodeData,
            PortIndex port) = 0;

  virtual
  std::shared_ptr<NodeData>
  outData(PortIndex port) = 0;

	virtual std::vector<QWidget *> embeddedWidget() = 0;

  virtual
  bool
  resizable() const { return false; }

	virtual std::string getShaderCode() = 0;
	virtual DFNodeType getNodeType() const = 0;
	virtual Mat4f addTranslation() { return Mat4f(); }
	virtual void setTransform(const Mat4f &_t) {}
  virtual void updateWidgets() {}
  static QString nodeCategory() { return QString("Primitive"); }

signals:

	void dataUpdated(PortIndex index);
	void dataInvalidated(PortIndex index);
	void computingStarted();
	void computingFinished();
};
