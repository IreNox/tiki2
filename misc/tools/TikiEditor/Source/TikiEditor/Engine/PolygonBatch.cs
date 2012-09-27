using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace TikiEditor
{
    public class PolygonBatch
    {
        #region Vars
        private bool _isActive;

        private float _layerDepth;

        private BasicEffect _effect;
        private GraphicsDevice _device;

        private List<PolygonInfo> _drawInfos = new List<PolygonInfo>();
        #endregion

        #region Init
        public PolygonBatch(GraphicsDevice device)
        {
            _device = device;
            _effect = new BasicEffect(_device);
            _effect.VertexColorEnabled = true;
        }
        #endregion

        #region Member
        public void Begin()
        {
            if (_isActive)
            {
                throw new Exception("PolygonBatch already started");
            }

            _isActive = true;
            _drawInfos.Clear();
        }

        public void End()
        {
            if (!_isActive)
            {
                throw new Exception("You must call PolygonBatch.Begin first");
            }

            _device.SamplerStates[0] = SamplerState.AnisotropicClamp;

            foreach (PolygonInfo info in _drawInfos)
            {
                info.Draw();
            }

            _drawInfos.Clear();
            _isActive = false;
        }
        #endregion

        #region Member - Draw - Lines
        public void DrawLine(Vector2 p1, Vector2 p2, Color color)
        {
            _effect.Projection = GI.Camera.ProjectionMatrix;
            _effect.View = GI.Camera.ViewMatrix;

            VertexPositionColor[] list = new VertexPositionColor[] {
                new VertexPositionColor(new Vector3(p1, 0), color),
                new VertexPositionColor(new Vector3(p2, 0), color)
            };

            VertexBuffer vb = new VertexBuffer(GI.Device, VertexPositionColor.VertexDeclaration, 2, BufferUsage.WriteOnly);
            vb.SetData(list);

            _drawInfos.Add(
                new PolygonInfo(PrimitiveType.LineList, vb, null, _effect, Matrix.Identity, true)
            );
        }

        public void DrawLine(Vector2[] vertices, Color color)
        {
            int c = vertices.Length - 1;
            List<VertexPositionColor> list = new List<VertexPositionColor>();

            for (int i = 0; i < c; i++)
            {
                list.Add(new VertexPositionColor(new Vector3(vertices[i], 0), color));
                list.Add(new VertexPositionColor(new Vector3(vertices[i + 1], 0), color));
            }

            list.Add(new VertexPositionColor(new Vector3(vertices.Last(), 0), color));
            list.Add(new VertexPositionColor(new Vector3(vertices.First(), 0), color));

            VertexBuffer vb = new VertexBuffer(GI.Device, VertexPositionColor.VertexDeclaration, list.Count, BufferUsage.WriteOnly);
            vb.SetData(list.ToArray());

            _drawInfos.Add(
                new PolygonInfo(PrimitiveType.LineList, vb, null, _effect, Matrix.Identity, true)
            );
        }

        public void DrawLine(VertexBuffer vertexBuffer, IndexBuffer indexBuffer)
        {
            _drawInfos.Add(
                new PolygonInfo(PrimitiveType.LineList, vertexBuffer, indexBuffer, _effect, Matrix.Identity, false)
            );
        }
        #endregion

        #region Member - Draw - Triangles
        public void Draw(Vector2[] vertices, Color color)
        {
            if (vertices.Length < 3) return;

            int c = vertices.Length - 1;
            List<VertexPositionColor> list = new List<VertexPositionColor>();

            for (int i = 1; i < c; i++)
            {
                list.Add(new VertexPositionColor(new Vector3(vertices[0], 0), color));
                list.Add(new VertexPositionColor(new Vector3(vertices[i], 0), color));
                list.Add(new VertexPositionColor(new Vector3(vertices[i + 1], 0), color));
            }

            VertexBuffer vb = new VertexBuffer(GI.Device, VertexPositionColor.VertexDeclaration, list.Count, BufferUsage.WriteOnly);
            vb.SetData(list.ToArray());

            _drawInfos.Add(
                new PolygonInfo(PrimitiveType.TriangleList, vb, null, _effect, Matrix.Identity, true)
            );
        }

        public void Draw(VertexBuffer vertexBuffer, IndexBuffer indexBuffer, Color color)
        {
            BasicEffect effect = new BasicEffect(_device);
            effect.VertexColorEnabled = true;
            effect.Projection = GI.Camera.ProjectionMatrix;
            effect.View = GI.Camera.ViewMatrix;

            this.Draw(vertexBuffer, indexBuffer, effect, Matrix.Identity);
        }

        public void Draw(VertexBuffer vertexBuffer, IndexBuffer indexBuffer, Texture2D texture)
        {
            BasicEffect effect = new BasicEffect(_device);
            effect.TextureEnabled = true;
            effect.Texture = texture;
            effect.Projection = GI.Camera.ProjectionMatrix;
            effect.View = GI.Camera.ViewMatrix;

            this.Draw(vertexBuffer, indexBuffer, effect, Matrix.Identity);
        }

        public void Draw(VertexBuffer vertexBuffer, IndexBuffer indexBuffer, Effect effect, Matrix worldMatrix)
        {
            _drawInfos.Add(
                new PolygonInfo(
                    PrimitiveType.TriangleList,
                    vertexBuffer,
                    indexBuffer,
                    effect,
                    worldMatrix,
                    false
                )
            );
        }
        #endregion

        #region Properties
        public float LayerDepth
        {
            get { return _layerDepth; }
            set { _layerDepth = value; }
        }
        #endregion

        #region Class - PolygonInfo
        private class PolygonInfo
        {
            #region Vars
            public PrimitiveType PrimitiveType;

            public Effect Effect;
            public Matrix WorldMatrix;

            public IndexBuffer IndexBuffer;
            public VertexBuffer VertexBuffer;

            private GraphicsDevice _device;

            private bool _destroyBuffer = false;
            #endregion

            #region Init
            public PolygonInfo(PrimitiveType type, VertexBuffer vertexBuffer, IndexBuffer indexBuffer, Effect effect, Matrix worldMatrix, bool destroyBuffer)
            {
                this.Effect = effect;
                this.WorldMatrix = worldMatrix;

                this.PrimitiveType = type;
                this.IndexBuffer = indexBuffer;
                this.VertexBuffer = vertexBuffer;

                _device = GI.Device;

                _destroyBuffer = destroyBuffer;
            }
            #endregion

            #region Member
            public void Draw()
            {
                if (this.Effect is BasicEffect)
                {
                    BasicEffect e = (BasicEffect)this.Effect;

                    e.View = GI.Camera.ViewMatrix;
                    e.Projection = GI.Camera.ProjectionMatrix;
                    e.World = this.WorldMatrix;
                }
                else
                {
                    this.Effect.Parameters["World"].SetValue(this.WorldMatrix);
                }

                _device.SetVertexBuffer(this.VertexBuffer);

                if (this.IndexBuffer != null)
                {
                    _device.Indices = this.IndexBuffer;
                }

                if (this.PrimitiveType == PrimitiveType.TriangleList)
                {
                    foreach (var pass in this.Effect.CurrentTechnique.Passes)
                    {
                        pass.Apply();

                        if (this.IndexBuffer == null)
                        {
                            GI.Device.SetVertexBuffer(this.VertexBuffer);
                            GI.Device.DrawPrimitives(
                                PrimitiveType.TriangleList,
                                0,
                                this.VertexBuffer.VertexCount / 3
                            );
                        }
                        else
                        {
                            GI.Device.DrawIndexedPrimitives(
                                PrimitiveType.TriangleList,
                                0,
                                0,
                                this.VertexBuffer.VertexCount,
                                0,
                                this.IndexBuffer.IndexCount / 3
                            );
                        }
                    }
                }
                else if (this.PrimitiveType == PrimitiveType.LineList)
                {
                    foreach (var pass in this.Effect.CurrentTechnique.Passes)
                    {
                        pass.Apply();

                        if (this.IndexBuffer == null)
                        {
                            GI.Device.DrawPrimitives(
                                PrimitiveType.LineList,
                                0,
                                this.VertexBuffer.VertexCount / 2
                            );
                        }
                        else
                        {
                            GI.Device.DrawIndexedPrimitives(
                                PrimitiveType.LineList,
                                0,
                                0,
                                this.VertexBuffer.VertexCount,
                                0,
                                this.IndexBuffer.IndexCount / 2
                            );
                        }
                    }

                    if (_destroyBuffer) this.VertexBuffer.Dispose();
                }
            }
            #endregion
        }
        #endregion
    }
}
