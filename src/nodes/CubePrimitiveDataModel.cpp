#include "CubePrimitiveDataModel.hpp"

#include <QtGui/QDoubleValidator>

CubePrimitiveDataModel::
CubePrimitiveDataModel()
  : _lineEdit(new QLineEdit())
{
  _lineEdit->setValidator(new QDoubleValidator());

  _lineEdit->setMaximumSize(_lineEdit->sizeHint());

  connect(_lineEdit, &QLineEdit::textChanged,
          this, &CubePrimitiveDataModel::onTextEdited);

  _lineEdit->setText("0.0");
}


void
CubePrimitiveDataModel::
save(Properties &p) const
{
  p.put("model_name", CubePrimitiveDataModel::name());

  if (_number)
    p.put("number", _number->number());
}


void
CubePrimitiveDataModel::
restore(Properties const &p)
{
  double number;

  if (bool ok = p.get("number", &number))
  {
    _number = std::make_shared<NumberData>(number);
    _lineEdit->setText(QString::number(number));
  }
}


unsigned int
CubePrimitiveDataModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 0;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}


void
CubePrimitiveDataModel::
onTextEdited(QString const &string)
{
  Q_UNUSED(string);

  bool ok = false;

  double number = _lineEdit->text().toDouble(&ok);

  if (ok)
  {
    _number = std::make_shared<NumberData>(number);

    emit dataUpdated(0);
  }
  else
  {
    emit dataInvalidated(0);
  }
}


NodeDataType
CubePrimitiveDataModel::
dataType(PortType, PortIndex) const
{
  return NumberData().type();
}


std::shared_ptr<NodeData>
CubePrimitiveDataModel::
outData(PortIndex)
{
  return _number;
}
