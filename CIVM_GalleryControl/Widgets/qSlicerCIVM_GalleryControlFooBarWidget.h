/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

#ifndef __qSlicerCIVM_GalleryControlFooBarWidget_h
#define __qSlicerCIVM_GalleryControlFooBarWidget_h

// Qt includes
#include <QWidget>

// FooBar Widgets includes
#include "qSlicerCIVM_GalleryControlModuleWidgetsExport.h"

class qSlicerCIVM_GalleryControlFooBarWidgetPrivate;

/// \ingroup Slicer_QtModules_CIVM_GalleryControl
class Q_SLICER_MODULE_CIVM_GALLERYCONTROL_WIDGETS_EXPORT qSlicerCIVM_GalleryControlFooBarWidget
  : public QWidget
{
  Q_OBJECT
public:
  typedef QWidget Superclass;
  qSlicerCIVM_GalleryControlFooBarWidget(QWidget *parent=0);
  virtual ~qSlicerCIVM_GalleryControlFooBarWidget();

protected slots:
  void ButtonTest();
protected:
  QScopedPointer<qSlicerCIVM_GalleryControlFooBarWidgetPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerCIVM_GalleryControlFooBarWidget);
  Q_DISABLE_COPY(qSlicerCIVM_GalleryControlFooBarWidget);
};

#endif
